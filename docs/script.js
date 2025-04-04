async function loadTemplates(language) {
    try {
        const response = await fetch(`templates_${language}.json`);
        if (!response.ok) {
            throw new Error(`无法加载${language}模板: ${response.status}`);
        }
        const templates = await response.json();
        
        // 生成侧边栏目录树
        generateSidebar(templates, language);
        
        // 清空主内容区
        const content = document.getElementById('content');
        content.innerHTML = '';
        
        // 渲染文件内容
        renderTemplates(templates, content, language);
        
        // 确保代码高亮在DOM更新后执行
        setTimeout(() => {
            hljs.highlightAll();
        }, 100);
        
        // 更新当前语言状态
        document.querySelectorAll('.nav-buttons button').forEach(btn => {
            if (btn.getAttribute('data-lang') === language) {
                btn.classList.add('active');
            } else {
                btn.classList.remove('active');
            }
        });
    } catch (error) {
        console.error('加载模板失败:', error);
        document.getElementById('content').innerHTML = `<div class="error">加载模板失败: ${error.message}</div>`;
    }
}

function generateSidebar(templates, language) {
    const sidebar = document.getElementById('sidebar');
    sidebar.innerHTML = '';
    
    for (const category in templates) {
        if (category === 'root') continue;
        
        const categoryDiv = document.createElement('div');
        categoryDiv.className = 'sidebar-category';
        
        const categoryTitle = document.createElement('h3');
        categoryTitle.textContent = category;
        categoryDiv.appendChild(categoryTitle);
        
        const filesList = document.createElement('div');
        filesList.className = 'sidebar-files';
        
        for (const fileName in templates[category]) {
            const fileLink = document.createElement('div');
            fileLink.className = 'sidebar-file';
            fileLink.textContent = fileName;
            fileLink.onclick = () => scrollToFile(category, fileName);
            filesList.appendChild(fileLink);
        }
        
        categoryDiv.appendChild(filesList);
        sidebar.appendChild(categoryDiv);
    }
}

function scrollToFile(category, fileName) {
    // 使用安全的ID生成方式
    const safeId = `file-${encodeURIComponent(category)}-${encodeURIComponent(fileName)}`;
    const fileElement = document.getElementById(safeId);
    if (fileElement) {
        fileElement.scrollIntoView({ behavior: 'smooth' });
    }
}

function renderTemplates(templates, container, language) {
    for (const category in templates) {
        const section = document.createElement('div');
        section.className = 'template-section';
        
        const title = document.createElement('h2');
        title.textContent = category === 'root' ? '根目录' : category;
        section.appendChild(title);
        
        for (const [name, code] of Object.entries(templates[category])) {
            const fileWrapper = document.createElement('div');
            fileWrapper.className = 'file-wrapper';
            // 使用安全的ID生成方式
            fileWrapper.id = `file-${encodeURIComponent(category)}-${encodeURIComponent(name)}`;
            
            const fileName = document.createElement('h3');
            fileName.textContent = name;
            fileWrapper.appendChild(fileName);
            
            const pre = document.createElement('pre');
            const codeElement = document.createElement('code');
            // 根据文件扩展名设置语言
            const fileExt = name.split('.').pop().toLowerCase();
            const codeLanguage = fileExt === 'py' ? 'python' : 
                                (fileExt === 'cpp' || fileExt === 'hpp') ? 'cpp' : language;
            
            codeElement.className = codeLanguage;
            // 确保代码内容正确显示
            codeElement.textContent = code;
            pre.appendChild(codeElement);
            fileWrapper.appendChild(pre);
            
            section.appendChild(fileWrapper);
        }
        
        container.appendChild(section);
    }
}

// 默认加载C++模板
window.onload = () => {
    // 为语言按钮添加事件监听器和数据属性
    document.querySelectorAll('.nav-buttons button').forEach(btn => {
        const lang = btn.textContent.toLowerCase();
        btn.setAttribute('data-lang', lang);
        btn.onclick = () => showLanguage(lang);
    });
    
    // 默认加载C++模板
    loadTemplates('cpp');
};

// 语言切换函数
function showLanguage(language) {
    loadTemplates(language);
}