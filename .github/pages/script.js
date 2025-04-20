// 添加全局变量来跟踪当前语言
let currentLanguage = null;

async function loadTemplates(language) {
    // 检查是否点击了当前已加载的语言
    if (language === currentLanguage) {
        // 找到对应的按钮
        const button = document.querySelector(`.language-selector button[onclick="loadTemplates('${language}')"]`);
        if (button) {
            // 添加动画类
            button.classList.add('already-done');
            // 移除动画类
            setTimeout(() => {
                button.classList.remove('already-done');
            }, 500); // 动画持续时间应与 CSS 中定义的一致
        }
        return; // 阻止重新加载
    }

    try {
        const response = await fetch(`templates_${language}.json`);
        if (!response.ok) {
            throw new Error(`无法加载${language}模板: ${response.status}`);
        }
        const templates = await response.json();

        // 清空主内容区
        const content = document.getElementById('content');
        content.innerHTML = '';

        // 添加语言选择器
        const langSelector = document.createElement('div');
        langSelector.className = 'language-selector';
        // 注意：这里直接使用了 onclick，如果后续改为 addEventListener 会更健壮
        langSelector.innerHTML = `
            <button class="${language === 'cpp' ? 'active' : ''}" onclick="loadTemplates('cpp')">C++</button>
            <button class="${language === 'python' ? 'active' : ''}" onclick="loadTemplates('python')">Python</button>
        `;
        content.appendChild(langSelector);

        // 创建按钮容器
        const buttonContainer = document.createElement('div');
        buttonContainer.className = 'global-actions-container';

        // 添加一键折叠按钮
        const collapseAllBtn = document.createElement('button');
        collapseAllBtn.id = 'collapse-all-btn';
        collapseAllBtn.innerHTML = '<i class="fas fa-compress-alt"></i> 一键折叠';
        collapseAllBtn.onclick = function() {
            const allCodeBlocks = document.querySelectorAll('.code-block');
            let anyVisible = false; // 标记是否有可见的代码块
            allCodeBlocks.forEach(block => {
                if (block.style.display !== 'none') {
                    anyVisible = true;
                    block.style.display = 'none';
                    // 找到对应的展开/收起按钮并更新图标
                    const expandBtn = block.closest('.template-card').querySelector('.expand-btn');
                    if (expandBtn) {
                        expandBtn.innerHTML = '<i class="fas fa-chevron-down"></i>';
                    }
                }
            });
            // 如果没有任何可见的代码块（即已经全部折叠），则触发动画
            if (!anyVisible) {
                this.classList.add('already-done');
                setTimeout(() => {
                    this.classList.remove('already-done');
                }, 500); // 动画持续时间
            }
        };
        buttonContainer.appendChild(collapseAllBtn); // 添加到容器

        // 添加一键展开按钮
        const expandAllBtn = document.createElement('button');
        expandAllBtn.id = 'expand-all-btn';
        expandAllBtn.innerHTML = '<i class="fas fa-expand-alt"></i> 一键展开';
        expandAllBtn.onclick = function() {
            const allCodeBlocks = document.querySelectorAll('.code-block');
            let anyHidden = false; // 标记是否有隐藏的代码块
            allCodeBlocks.forEach(block => {
                if (block.style.display === 'none' || !block.style.display) {
                    anyHidden = true;
                    block.style.display = 'block';
                    // 找到对应的展开/收起按钮并更新图标
                    const expandBtn = block.closest('.template-card').querySelector('.expand-btn');
                    if (expandBtn) {
                        expandBtn.innerHTML = '<i class="fas fa-chevron-up"></i>';
                    }
                }
            });
            // 如果没有任何隐藏的代码块（即已经全部展开），则触发动画
            if (!anyHidden) {
                this.classList.add('already-done');
                setTimeout(() => {
                    this.classList.remove('already-done');
                }, 500); // 动画持续时间
            }
        };
        buttonContainer.appendChild(expandAllBtn); // 添加到容器

        content.appendChild(buttonContainer); // 将按钮容器添加到内容区域

        // 添加页面标题
        const title = document.createElement('h1');
        title.textContent = `CP Template (${language.toUpperCase()})`;
        content.appendChild(title);


        // 渲染模板卡片
        renderTemplateCards(templates, content, language);

        // 高亮所有代码块
        hljs.highlightAll();

        // 添加回到顶部按钮
        addBackToTopButton();

        // 更新当前语言状态
        currentLanguage = language;

    } catch (error) {
        const content = document.getElementById('content');
        content.innerHTML = `<div class="error">${error.message}</div>`;
        console.error(error);
        // 如果加载失败，重置当前语言状态，允许用户重试
        currentLanguage = null;
    }
}

// 在renderTemplateCards函数中修改卡片创建部分
function renderTemplateCards(templates, container, language) {
    // 创建分类索引
    const categoriesDiv = document.createElement('div');
    categoriesDiv.className = 'categories-index';
    categoriesDiv.innerHTML = '<h2>目录</h2>';
    
    const categoriesList = document.createElement('ul');
    categoriesDiv.appendChild(categoriesList);
    
    // 添加分类索引到容器
    container.appendChild(categoriesDiv);
    
    // 按分类渲染模板
    for (const category in templates) {
        // 添加分类到索引
        const categoryItem = document.createElement('li');
        const categoryLink = document.createElement('a');
        categoryLink.href = `#category-${encodeURIComponent(category)}`;
        categoryLink.textContent = category === 'root' ? '根目录' : category;
        categoryItem.appendChild(categoryLink);
        categoriesList.appendChild(categoryItem);
        
        // 创建分类区域
        const categorySection = document.createElement('div');
        categorySection.className = 'category-section';
        categorySection.id = `category-${encodeURIComponent(category)}`;
        
        const categoryTitle = document.createElement('h2');
        categoryTitle.textContent = category === 'root' ? '根目录' : category;
        categorySection.appendChild(categoryTitle);
        
        // 创建该分类下的模板卡片
        const categoryCards = document.createElement('div');
        categoryCards.className = 'category-cards';
        
        // 在创建模板卡片的部分进行修改
        for (const [name, code] of Object.entries(templates[category])) {
            const card = document.createElement('div');
            card.className = 'template-card';
            
            const cardHeader = document.createElement('div');
            cardHeader.className = 'card-header';
            
            const fileName = document.createElement('h3');
            fileName.textContent = name;
            cardHeader.appendChild(fileName);
            
            const cardButtons = document.createElement('div');
            cardButtons.className = 'card-buttons';
            
            const copyBtn = document.createElement('button');
            copyBtn.className = 'copy-btn';
            copyBtn.innerHTML = '<i class="fas fa-copy"></i>';
            copyBtn.title = '复制代码';
            copyBtn.onclick = function() {
                navigator.clipboard.writeText(code).then(() => {
                    this.innerHTML = '<i class="fas fa-check"></i>';
                    this.classList.add('copied');
                    setTimeout(() => {
                        this.innerHTML = '<i class="fas fa-copy"></i>';
                        this.classList.remove('copied');
                    }, 2000);
                });
            };
            cardButtons.appendChild(copyBtn);
            
            const expandBtn = document.createElement('button');
            expandBtn.className = 'expand-btn';
            expandBtn.innerHTML = '<i class="fas fa-chevron-down"></i>';
            expandBtn.title = '展开/收起';
            expandBtn.onclick = function() {
                const codeBlock = this.closest('.template-card').querySelector('.code-block');
                if (codeBlock.style.display === 'none' || !codeBlock.style.display) {
                    codeBlock.style.display = 'block';
                    this.innerHTML = '<i class="fas fa-chevron-up"></i>';
                } else {
                    codeBlock.style.display = 'none';
                    this.innerHTML = '<i class="fas fa-chevron-down"></i>';
                }
            };
            cardButtons.appendChild(expandBtn);
            
            cardHeader.appendChild(cardButtons);
            card.appendChild(cardHeader);
            
            const codeBlock = document.createElement('div');
            codeBlock.className = 'code-block';
            codeBlock.style.display = 'none';
            
            const pre = document.createElement('pre');
            const codeElement = document.createElement('code');
            // 根据文件扩展名设置语言
            const fileExt = name.split('.').pop().toLowerCase();
            const codeLanguage = fileExt === 'py' ? 'python' : 
                          (fileExt === 'cpp' || fileExt === 'hpp') ? 'cpp' : language;
            
            codeElement.className = codeLanguage;
            codeElement.textContent = code;
            pre.appendChild(codeElement);
            codeBlock.appendChild(pre);
            
            card.appendChild(codeBlock);
            categoryCards.appendChild(card);
        }
        
        categorySection.appendChild(categoryCards);
        container.appendChild(categorySection);
    }
}

// 添加回到顶部按钮
function addBackToTopButton() {
    // 移除已存在的按钮（如果有）
    const existingButton = document.getElementById('back-to-top');
    if (existingButton) {
        existingButton.remove();
    }
    
    // 创建回到顶部按钮
    const backToTopBtn = document.createElement('button');
    backToTopBtn.id = 'back-to-top';
    // 使用 Font Awesome 图标替换原来的文字
    backToTopBtn.innerHTML = '<i class="fas fa-arrow-up"></i>';
    backToTopBtn.title = '回到顶部';
    document.body.appendChild(backToTopBtn);
    
    // 添加点击事件
    backToTopBtn.addEventListener('click', () => {
        window.scrollTo({
            top: 0,
            behavior: 'smooth'
        });
    });
    
    // 监听滚动事件，控制按钮显示/隐藏
    window.addEventListener('scroll', () => {
        if (window.scrollY > 300) {
            backToTopBtn.classList.add('visible');
        } else {
            backToTopBtn.classList.remove('visible');
        }
    });
}

// 页面加载时默认显示C++模板
// 修改 window.onload 以确保初始语言状态被设置
window.onload = () => {
    loadTemplates('cpp');
};


// 添加复制功能的辅助函数
function copyToClipboard(text) {
    // 创建临时文本区域
    const textArea = document.createElement('textarea');
    textArea.value = text;
    document.body.appendChild(textArea);
    textArea.select();

    try {
        // 执行复制命令
        document.execCommand('copy');
        return true;
    } catch (err) {
        console.error('复制失败:', err);
        return false;
    } finally {
        // 移除临时文本区域
        document.body.removeChild(textArea);
    }
}