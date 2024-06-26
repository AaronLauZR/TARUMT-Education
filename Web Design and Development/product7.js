const btns = document.querySelectorAll('.btn');
const storeProducts = document.querySelectorAll('.store-product');

for (i = 0; i < btns.length; i++){
    btns[i].addEventListener('click', (e) => {
        e.preventDefault();

        const filter = e.target.dataset.filter; 
        console.log(filter);   
        storeProducts.forEach((product)=> {
            if (filter === 'all'){
                product.style.display = 'block'
            } else{
                if (product.classList.contains(filter)){
                    product.style.display = 'block'
                } else{
                    product.style.display = 'none'
                }
            }
        });
    });
};


/*const search = document.getElementById("search");
//const productName = document.querySelectorAll(".product-details h3");



search.addEventListener("keyup", (e) =>{
    e.preventDefault();
    const searchValue = search.value.toLowerCase().trim();

    for (i = 0; i< storeProducts.length; i++){
        if (storeProducts[i].classList.contains(searchValue)){
            storeProducts[i].style.display = 'block';
        }
        else if(searchValue == ""){
            storeProducts[i].style.display = 'block';
        }else{
            storeProducts[i].style.display = 'none';
        }

    }

})*/

// SEARCH FILTER
const search = document.getElementById("search");
const productName = document.querySelectorAll(".product-details h3");

// A BETTER WAY TO FILTER THROUGH THE PRODUCTS
search.addEventListener("keyup", filterProducts);


function filterProducts(e) {
    const text = e.target.value.toLowerCase();
    // console.log(productName[0]);
    productName.forEach(function(product) {
        const item = product.firstChild.textContent;
        if (item.toLowerCase().indexOf(text) != -1) {
            product.parentElement.parentElement.style.display = "block"
        } else {
            product.parentElement.parentElement.style.display = "none"
        }
    })
}