async function loadTemplates(language) {
    const response = await fetch(`templates_${language}.json`);
    const templates = await response.json();
    
    const content = document.getElementById('content');
    content.innerHTML = '';
    
    for (const category in templates) {
        const section = document.createElement('div');
        section.className = 'template-section';
        
        const title = document.createElement('h2');
        title.textContent = category;
        section.appendChild(title);
        
        for (const [name, code] of Object.entries(templates[category])) {
            const pre = document.createElement('pre');
            const codeElement = document.createElement('code');
            codeElement.className = language;
            codeElement.textContent = code;
            pre.appendChild(codeElement);
            section.appendChild(pre);
        }
        
        content.appendChild(section);
    }
    
    hljs.highlightAll();
}

function showLanguage(language) {
    loadTemplates(language);
}

// 默认加载C++模板
window.onload = () => loadTemplates('cpp');