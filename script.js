// 全局状态：当前已加载的语言
let currentLanguage = null;
// 全局状态：已缓存的模板数据，避免重复 fetch
const templateCache = new Map();
// 标记回到顶部按钮是否已初始化，避免重复绑定 scroll 监听器
let backToTopInitialized = false;

const LANGUAGES = [
    { key: 'cpp', label: 'C++' },
    { key: 'python', label: 'Python' },
];

// 将任意字符串转为合法且稳定的 DOM id，同时保证 hash 跳转可用
function slugify(str) {
    return str.replace(/[^a-zA-Z0-9_-]/g, '_');
}

// 根据文件扩展名推断 highlight.js 语言
function inferLanguage(fileName, fallback) {
    const ext = fileName.split('.').pop().toLowerCase();
    if (ext === 'py') return 'python';
    if (ext === 'cpp' || ext === 'hpp') return 'cpp';
    return fallback;
}

// 触发"已是无操作"的晃动动画
function triggerShake(button) {
    if (!button) return;
    button.classList.add('already-done');
    setTimeout(() => button.classList.remove('already-done'), 500);
}

async function loadTemplates(language) {
    // 点击当前已加载的语言时，仅触发动画提示，不重新渲染
    if (language === currentLanguage) {
        const button = document.querySelector(
            `.language-selector button[data-lang="${language}"]`
        );
        triggerShake(button);
        return;
    }

    const content = document.getElementById('content');
    content.innerHTML = '<div class="loading">加载中…</div>';

    try {
        // 命中缓存则不再发起网络请求
        let templates = templateCache.get(language);
        if (!templates) {
            const response = await fetch(`templates_${language}.json`);
            if (!response.ok) {
                throw new Error(`无法加载 ${language} 模板: ${response.status}`);
            }
            templates = await response.json();
            templateCache.set(language, templates);
        }

        renderPage(templates, language);
        currentLanguage = language;
    } catch (error) {
        content.innerHTML = `<div class="error">${error.message}</div>`;
        console.error(error);
        // 加载失败时重置状态，允许用户重试
        currentLanguage = null;
    }
}

function renderPage(templates, language) {
    const content = document.getElementById('content');
    content.innerHTML = '';

    // 语言选择器（使用 data-lang + 事件委托，避免内联 onclick）
    const langSelector = document.createElement('div');
    langSelector.className = 'language-selector';
    langSelector.innerHTML = LANGUAGES.map(
        ({ key, label }) =>
            `<button class="${key === language ? 'active' : ''}" data-lang="${key}">${label}</button>`
    ).join('');
    content.appendChild(langSelector);

    // 全局操作按钮（使用 data-action + 事件委托）
    const buttonContainer = document.createElement('div');
    buttonContainer.className = 'global-actions-container';
    buttonContainer.innerHTML = `
        <button id="collapse-all-btn" data-action="collapse-all">
            <i class="fas fa-compress-alt"></i> 一键折叠
        </button>
        <button id="expand-all-btn" data-action="expand-all">
            <i class="fas fa-expand-alt"></i> 一键展开
        </button>
    `;
    content.appendChild(buttonContainer);

    // 页面标题
    const title = document.createElement('h1');
    title.textContent = `CP Template (${language.toUpperCase()})`;
    content.appendChild(title);

    // 渲染分类索引 + 各分类卡片
    renderTemplateCards(templates, content);

    // 高亮所有代码块
    hljs.highlightAll();

    // 回到顶部按钮（仅初始化一次）
    addBackToTopButton();
}

// 渲染分类索引与各分类下的模板卡片
function renderTemplateCards(templates, container) {
    // 目录索引
    const categoriesDiv = document.createElement('div');
    categoriesDiv.className = 'categories-index';
    categoriesDiv.innerHTML = '<h2>目录</h2>';

    const categoriesList = document.createElement('ul');
    Object.keys(templates).forEach((category) => {
        const slug = slugify(category);
        const item = document.createElement('li');
        const link = document.createElement('a');
        link.href = `#category-${slug}`;
        link.textContent = category === 'root' ? '根目录' : category;
        item.appendChild(link);
        categoriesList.appendChild(item);
    });
    categoriesDiv.appendChild(categoriesList);
    container.appendChild(categoriesDiv);

    // 各分类区域
    Object.entries(templates).forEach(([category, files]) => {
        const slug = slugify(category);

        const section = document.createElement('div');
        section.className = 'category-section';
        section.id = `category-${slug}`;

        const title = document.createElement('h2');
        title.textContent = category === 'root' ? '根目录' : category;
        section.appendChild(title);

        const cards = document.createElement('div');
        cards.className = 'category-cards';

        Object.entries(files).forEach(([name, code]) => {
            cards.appendChild(buildCard(name, code));
        });

        section.appendChild(cards);
        container.appendChild(section);
    });
}

// 构建单张模板卡片
function buildCard(name, code) {
    const card = document.createElement('div');
    card.className = 'template-card';

    const header = document.createElement('div');
    header.className = 'card-header';

    const fileName = document.createElement('h3');
    fileName.textContent = name;
    header.appendChild(fileName);

    const buttons = document.createElement('div');
    buttons.className = 'card-buttons';
    buttons.innerHTML = `
        <button class="copy-btn" data-action="copy" title="复制代码" aria-label="复制代码">
            <i class="fas fa-copy"></i>
        </button>
        <button class="expand-btn" data-action="toggle" title="展开/收起" aria-label="展开/收起">
            <i class="fas fa-chevron-down"></i>
        </button>
    `;
    header.appendChild(buttons);
    card.appendChild(header);

    const codeBlock = document.createElement('div');
    codeBlock.className = 'code-block';
    codeBlock.style.display = 'none';

    const pre = document.createElement('pre');
    const codeElement = document.createElement('code');
    codeElement.className = inferLanguage(name, '');
    codeElement.textContent = code;
    pre.appendChild(codeElement);
    codeBlock.appendChild(pre);
    card.appendChild(codeBlock);

    return card;
}

// 全局事件委托：语言切换 + 折叠/展开 + 复制 + 单卡展开收起
function initGlobalDelegation() {
    document.addEventListener('click', (event) => {
        const target = event.target.closest('[data-action], [data-lang]');
        if (!target) return;

        if (target.dataset.lang) {
            loadTemplates(target.dataset.lang);
            return;
        }

        switch (target.dataset.action) {
            case 'copy':
                handleCopy(target);
                break;
            case 'toggle':
                handleToggle(target);
                break;
            case 'collapse-all':
                setAllCodeBlocks(false, target);
                break;
            case 'expand-all':
                setAllCodeBlocks(true, target);
                break;
        }
    });
}

function handleCopy(button) {
    const card = button.closest('.template-card');
    const code = card?.querySelector('code')?.textContent ?? '';
    if (!code) return;

    if (!navigator.clipboard?.writeText) {
        triggerShake(button);
        return;
    }
    navigator.clipboard.writeText(code).then(
        () => {
            button.innerHTML = '<i class="fas fa-check"></i>';
            button.classList.add('copied');
            setTimeout(() => {
                button.innerHTML = '<i class="fas fa-copy"></i>';
                button.classList.remove('copied');
            }, 2000);
        },
        (err) => {
            console.error('复制失败:', err);
            triggerShake(button);
        }
    );
}

function handleToggle(button) {
    const codeBlock = button.closest('.template-card')?.querySelector('.code-block');
    if (!codeBlock) return;
    const willShow = codeBlock.style.display === 'none' || !codeBlock.style.display;
    codeBlock.style.display = willShow ? 'block' : 'none';
    button.innerHTML = willShow
        ? '<i class="fas fa-chevron-up"></i>'
        : '<i class="fas fa-chevron-down"></i>';
}

function setAllCodeBlocks(show, originButton) {
    const blocks = document.querySelectorAll('.code-block');
    let changed = false;
    blocks.forEach((block) => {
        const isVisible = block.style.display !== 'none';
        if (show && !isVisible) {
            block.style.display = 'block';
            changed = true;
        } else if (!show && isVisible) {
            block.style.display = 'none';
            changed = true;
        }
        const expandBtn = block.closest('.template-card')?.querySelector('.expand-btn');
        if (expandBtn) {
            expandBtn.innerHTML = show
                ? '<i class="fas fa-chevron-up"></i>'
                : '<i class="fas fa-chevron-down"></i>';
        }
    });
    // 如果没有任何变化（即已经是目标状态），触发动画提示
    if (!changed) triggerShake(originButton);
}

// 回到顶部按钮：仅创建一次，scroll 监听器也只绑定一次
function addBackToTopButton() {
    if (backToTopInitialized) return;
    backToTopInitialized = true;

    const btn = document.createElement('button');
    btn.id = 'back-to-top';
    btn.innerHTML = '<i class="fas fa-arrow-up"></i>';
    btn.title = '回到顶部';
    btn.setAttribute('aria-label', '回到顶部');
    document.body.appendChild(btn);

    btn.addEventListener('click', () => {
        window.scrollTo({ top: 0, behavior: 'smooth' });
    });

    window.addEventListener('scroll', () => {
        btn.classList.toggle('visible', window.scrollY > 300);
    });
}

// 页面加载完成后初始化
document.addEventListener('DOMContentLoaded', () => {
    initGlobalDelegation();
    loadTemplates('cpp');
});
