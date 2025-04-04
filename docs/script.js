async function loadTemplates(language) {
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
        langSelector.innerHTML = `
            <button class="${language === 'cpp' ? 'active' : ''}" onclick="loadTemplates('cpp')">C++</button>
            <button class="${language === 'python' ? 'active' : ''}" onclick="loadTemplates('python')">Python</button>
        `;
        content.appendChild(langSelector);
        
        // 添加标题
        const title = document.createElement('h1');
        title.textContent = `${language === 'cpp' ? 'C++' : 'Python'} 模板库`;
        content.appendChild(title);
        
        // 创建模板卡片容器
        const cardsContainer = document.createElement('div');
        cardsContainer.className = 'template-cards';
        content.appendChild(cardsContainer);
        
        // 渲染所有模板卡片
        renderTemplateCards(templates, cardsContainer, language);
        
        // 添加回到顶部按钮
        addBackToTopButton();
        
        // 确保代码高亮在DOM更新后执行
        setTimeout(() => {
            hljs.highlightAll();
        }, 100);
    } catch (error) {
        console.error('加载模板失败:', error);
        document.getElementById('content').innerHTML = `<div class="error">加载模板失败: ${error.message}</div>`;
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
            copyBtn.textContent = '复制';
            copyBtn.onclick = function() {
                navigator.clipboard.writeText(code).then(() => {
                    this.textContent = '已复制';
                    this.classList.add('copied');
                    setTimeout(() => {
                        this.textContent = '复制';
                        this.classList.remove('copied');
                    }, 2000);
                });
            };
            cardButtons.appendChild(copyBtn);
            
            const expandBtn = document.createElement('button');
            expandBtn.className = 'expand-btn';
            expandBtn.textContent = '展开';
            expandBtn.onclick = function() {
                const codeBlock = this.closest('.template-card').querySelector('.code-block');
                
                if (codeBlock.classList.contains('expanded')) {
                    // 收起动画
                    codeBlock.style.maxHeight = codeBlock.scrollHeight + 'px';
                    // 强制回流
                    codeBlock.offsetHeight;
                    codeBlock.style.maxHeight = '0';
                    codeBlock.classList.remove('expanded');
                    this.textContent = '展开';
                    
                    // 动画结束后隐藏
                    setTimeout(() => {
                        if (!codeBlock.classList.contains('expanded')) {
                            codeBlock.style.display = 'none';
                        }
                    }, 300);
                } else {
                    // 展开动画
                    codeBlock.style.display = 'block';
                    // 强制回流
                    codeBlock.offsetHeight;
                    codeBlock.style.maxHeight = '0';
                    // 强制回流
                    codeBlock.offsetHeight;
                    codeBlock.style.maxHeight = codeBlock.scrollHeight + 'px';
                    codeBlock.classList.add('expanded');
                    this.textContent = '收起';
                    
                    // 动画结束后移除高度限制
                    setTimeout(() => {
                        if (codeBlock.classList.contains('expanded')) {
                            codeBlock.style.maxHeight = 'none';
                        }
                    }, 300);
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
    backToTopBtn.innerHTML = '↑';
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
window.onload = () => loadTemplates('cpp');


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