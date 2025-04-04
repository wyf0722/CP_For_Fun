async function loadTemplates(language) {
    const response = await fetch(`templates_${language}.json`);
    const templates = await response.json();
    
    // 生成侧边栏目录树
    generateSidebar(templates);
    
    // 清空主内容区
    const content = document.getElementById('content');
    content.innerHTML = '';
    
    // 渲染文件内容
    renderTemplates(templates, content);
    
    hljs.highlightAll();
}

function generateSidebar(templates) {
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
    const fileElement = document.getElementById(`${category}-${fileName}`);
    if (fileElement) {
        fileElement.scrollIntoView({ behavior: 'smooth' });
    }
}

function renderTemplates(templates, container) {
    for (const category in templates) {
        const section = document.createElement('div');
        section.className = 'template-section';
        
        const title = document.createElement('h2');
        title.textContent = category === 'root' ? '根目录' : category;
        section.appendChild(title);
        
        for (const [name, code] of Object.entries(templates[category])) {
            const fileWrapper = document.createElement('div');
            fileWrapper.className = 'file-wrapper';
            fileWrapper.id = `${category}-${name}`;
            
            const fileName = document.createElement('h3');
            fileName.textContent = name;
            fileWrapper.appendChild(fileName);
            
            const pre = document.createElement('pre');
            const codeElement = document.createElement('code');
            codeElement.className = language;
            codeElement.textContent = code;
            pre.appendChild(codeElement);
            fileWrapper.appendChild(pre);
            
            section.appendChild(fileWrapper);
        }
        
        container.appendChild(section);
    }
}

// 默认加载C++模板
window.onload = () => loadTemplates('cpp');