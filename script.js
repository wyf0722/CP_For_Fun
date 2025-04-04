async function loadTemplates(language) {
    const response = await fetch(`templates_${language}.json`);
    const templates = await response.json();
    
    const content = document.getElementById('content');
    content.innerHTML = '';
    
    // 创建面包屑导航
    const breadcrumb = document.createElement('div');
    breadcrumb.className = 'breadcrumb';
    content.appendChild(breadcrumb);
    
    // 按目录层级排序
    const sortedCategories = Object.keys(templates).sort((a, b) => {
        if (a === 'root') return -1;
        if (b === 'root') return 1;
        return a.localeCompare(b);
    });
    
    for (const category of sortedCategories) {
        const section = document.createElement('div');
        section.className = 'template-section';
        
        const title = document.createElement('h2');
        title.textContent = category === 'root' ? '根目录' : category;
        section.appendChild(title);
        
        // 添加文件列表
        const fileList = document.createElement('div');
        fileList.className = 'file-list';
        
        for (const [name, code] of Object.entries(templates[category])) {
            const fileWrapper = document.createElement('div');
            fileWrapper.className = 'file-wrapper';
            
            const fileName = document.createElement('h3');
            fileName.textContent = name;
            fileWrapper.appendChild(fileName);
            
            const pre = document.createElement('pre');
            const codeElement = document.createElement('code');
            codeElement.className = language;
            codeElement.textContent = code;
            pre.appendChild(codeElement);
            fileWrapper.appendChild(pre);
            
            fileList.appendChild(fileWrapper);
        }
        
        section.appendChild(fileList);
        content.appendChild(section);
    }
    
    hljs.highlightAll();
}

function showLanguage(language) {
    loadTemplates(language);
}

// 默认加载C++模板
window.onload = () => loadTemplates('cpp');