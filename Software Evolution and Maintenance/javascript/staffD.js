document.addEventListener("DOMContentLoaded", function() {

    let jsonData = [];
    let currentPage = 1;
    let itemsPerPage = 2;

    const csvFile = '../data/staff2.csv';
    fetch(csvFile)
            .then(response => response.text())
            .then(data => {
                            displayjson(data);
                            const itemsPerPageSelect = document.getElementById('itemsPerPageSelect');
                            itemsPerPageSelect.addEventListener('change', function() {
                                itemsPerPage = parseInt(this.value, 10); 
                                currentPage = 1; 
                                displayPage(currentPage);  
                                setupPaginationButtons();  
                            });
            })
            .catch(error => console.error('Error:', error));

    function displayjson(data) {
        const appDiv = document.getElementById('app');
        const rows = data.split('\n');

        const headers = rows[0].split(',');
        jsonData = [];

        rows.forEach((e, rowIndex) => {
            if (rowIndex === 0) return;
            let content = e.split(',');
            content = content.map(item => item.replace(/&/g, ","));
            const obj = {};
            headers.forEach((header, i) => {
                obj[header] = content[i];
            });
            jsonData.push(obj);
        });

        displayPage(currentPage);
        setupPaginationButtons();
    }

    function displayPage(pageNumber) {
        const appDiv = document.getElementById('app');
        appDiv.innerHTML = '';

        const startIndex = (pageNumber - 1) * itemsPerPage;
        const endIndex = startIndex + itemsPerPage;

        for (let i = startIndex; i < endIndex && i < jsonData.length; i++) {
            const divElement = document.createElement('div');
            divElement.classList.add('flex', 'flex-col', 'md:flex-row', 'items-center', 'mb-4', 'p-4', 'shadow-md', 'bg-white', 'rounded-md', 'w-full', 'md:w-3/4', 'mx-auto');

            const name = jsonData[i].Name ? jsonData[i].Name.replace(/\s+/g, '') : "default";
            const imagePath = `../images/staff/${name}.jpg`;

            let imgHtml = `<div class="mr-4 mb-4 md:mb-0 w-full md:w-auto">
                <img src="${imagePath}" alt="${name}" class="w-full max-w-60 md:w-60">
            </div>`;

            let jsonDataHtml = '<div class="w-full">';
            for (let key in jsonData[i]) {
                if(jsonData[i][key] !== "-") {
                    let extraClasses = getExtraClassesForKey(key);
                    let value = jsonData[i][key];

                    switch (key) {
                        case "Major_study":
                            value = "<strong class='font-bold'>Major of Study/Specialization:</strong> " + value;
                            break;
                        case "Interest":
                            value = "<strong class='font-bold'>Area of Interest:</strong> " + value;
                            break;
                        default:
                            break;
                    }

                    jsonDataHtml += `<p class="${extraClasses}">${value}</p>`;
                }
            }
            jsonDataHtml += '</div>';

            divElement.innerHTML = imgHtml + jsonDataHtml;
            appDiv.appendChild(divElement);
        }
    }

    function setupPaginationButtons() {
        const paginationDiv = document.getElementById('pagination');
        paginationDiv.innerHTML = '';
        paginationDiv.classList.add('ml-5', 'sm:ml-10', 'md:ml-20', 'lg:ml-40', 'xl:ml-[120px]');

        const pagesLabel = document.createElement('span');
        pagesLabel.innerText = 'PAGES';
        pagesLabel.classList.add('mr-2', 'font-bold');
        paginationDiv.appendChild(pagesLabel);

        const totalPages = Math.ceil(jsonData.length / itemsPerPage);

        for (let i = 1; i <= totalPages; i++) {
            const button = document.createElement('button');
            button.innerText = i;
            button.classList.add('mx-1', 'py-1', 'px-3', 'bg-blue-500', 'text-white', 'rounded-md', 'sm:py-2', 'sm:px-4');
            if (i === currentPage) {
                button.classList.add('bg-blue-700');
            }
            button.addEventListener('click', function() {
                currentPage = i;
                displayPage(currentPage);
                setupPaginationButtons();  
            });
            paginationDiv.appendChild(button);
        }
    }

    function getExtraClassesForKey(key) {
        let extraClasses = '';
        switch (key) {
            case "Name":
                extraClasses = 'font-bold text-3xl';
                break;
            case "Position":
                extraClasses = 'font-bold italic text-blue-500 text-2xl mb-2';
                break;
            case "Lecture":
                extraClasses = ' font-bold text-blue-500 text-2xl mb-2';
                break;
            default:
                extraClasses = 'text-gray-500';
                break;
        }
        return extraClasses;
    }

});
