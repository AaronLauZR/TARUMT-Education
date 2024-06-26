let carts = document.querySelectorAll('.add-cart');

let products = [ 
    {
        name: "Man Chester Tee (Promoted) ",
        tag: "manchestertee(promoted)",
        price: 129,
        inCart: 0
    },
    {
        name: "Taichi Flash 2019 Men's Basketball Shoes (Promoted)",
        tag: "taichiflash2019men'sbasketballshoes(promoted)",
        price: 430,
        inCart: 0
    },
    {
        name: "Portable Volleyball Sets (Promoted)",
        tag: "portablevolleyballsets(promoted)",
        price: 190,
        inCart: 0
    },
    {
        name: "Ping Pong icon T-shirt (Promoted)",
        tag: "pingpongicont-shirt(promoted)",
        price: 30,
        inCart: 0
    },
    {
        name: "Fallen Angel Series Sports Shoes (Promoted)",
        tag: "fallenangelseriessportsshoes(promoted)",
        price: 230,
        inCart: 0
    },
    {
        name: "W283 Soccer Sports Shoes (Promoted)",
        tag: "w283soccersportsshoes(promoted)",
        price: 165,
        inCart: 0
    },
    {
        name: "Mens Breathe Combat high-top basketball shoe (Promoted)",
        tag: "mensbreathecombathigh-topbasketballshoe(promoted)",
        price: 290,
        inCart: 0
    },
    {
        name: "Essential football training flat markers 10-pack (Promoted)",
        tag: "essentialfootballtrainingflatmarkers10-pack(promoted)",
        price: 19,
        inCart: 0
    },
    {
        name: "Graffiti Style Printing T-shirt Top Volleyball Sportswear (Promoted)",
        tag: "graffitistyleprintingt-shirttopvolleyballsportswear(promoted)",
        price: 89,
        inCart: 0
    },


]

for(let i=0; i< carts.length; i++) {
    carts[i].addEventListener('click', () => {
        cartNumbers(products[i]);
        totalCost(products[i]);
    });
}

function onLoadCartNumbers() {
    let productNumbers = localStorage.getItem('cartNumbers');
    if( productNumbers ) {
        document.querySelector('.cart span').textContent = productNumbers;
    }
}

function cartNumbers(product, action) {
    let productNumbers = localStorage.getItem('cartNumbers');
    productNumbers = parseInt(productNumbers);

    let cartItems = localStorage.getItem('productsInCart');
    cartItems = JSON.parse(cartItems);

    if( action ) {
        localStorage.setItem("cartNumbers", productNumbers - 1);
        document.querySelector('.cart span').textContent = productNumbers - 1;
        console.log("action running");
    } else if( productNumbers ) {
        localStorage.setItem("cartNumbers", productNumbers + 1);
        document.querySelector('.cart span').textContent = productNumbers + 1;
    } else {
        localStorage.setItem("cartNumbers", 1);
        document.querySelector('.cart span').textContent = 1;
    }
    setItems(product);
}

function setItems(product) {
    let productNumbers = localStorage.getItem('cartNumbers');
    productNumbers = parseInt(productNumbers);
    let cartItems = localStorage.getItem('productsInCart');
    cartItems = JSON.parse(cartItems);

    if(cartItems != null) {
        let currentProduct = product.tag;
    
        if( cartItems[currentProduct] == undefined ) {
            cartItems = {
                ...cartItems,
                [currentProduct]: product
            }
        } 
        cartItems[currentProduct].inCart += 1;

    } else {
        product.inCart = 1;
        cartItems = { 
            [product.tag]: product
        };
    }

    localStorage.setItem('productsInCart', JSON.stringify(cartItems));
}

function totalCost( product, action ) {
    let cart = localStorage.getItem("totalCost");

    if( action) {
        cart = parseInt(cart);

        localStorage.setItem("totalCost", cart - product.price);
    } else if(cart != null) {
        
        cart = parseInt(cart);
        localStorage.setItem("totalCost", cart + product.price);
    
    } else {
        localStorage.setItem("totalCost", product.price);
        let exist = localStorage.getItem('formData');
        if (!exist) {
            localStorage.clear();
        }
    }
}

function displayCart() {
    let cartItems = localStorage.getItem('productsInCart');
    cartItems = JSON.parse(cartItems);

    let cart = localStorage.getItem("totalCost");
    cart = parseInt(cart);

    let productContainer = document.querySelector('.products');
    
    if( cartItems && productContainer ) {
        productContainer.innerHTML = '';
        Object.values(cartItems).map(item => {
            productContainer.innerHTML += 
            `<div class="product">
                <ion-icon name="close-circle"></ion-icon>
                <img src="./image/All_product/${item.tag}.jpg" />
                <span class="sm-hide">${item.name}</span>
            </div>
            <div class="price sm-hide">$${item.price},00</div>
            <div class="quantity">
                <ion-icon class="decrease " name="arrow-dropleft-circle"></ion-icon>
                    <span>${item.inCart}</span>
                <ion-icon class="increase" name="arrow-dropright-circle"></ion-icon>   
            </div>
            <div class="total">$${item.inCart * item.price}.00</div>`;
        });

        productContainer.innerHTML += `
            <div class="basketTotalContainer">
                <h4 class="basketTotalTitle">Basket Total</h4>
                <h4 class="basketTotal">$${cart},00</h4>
            </div>`

        deleteButtons();
        manageQuantity();
    }
}

function manageQuantity() {
    let decreaseButtons = document.querySelectorAll('.decrease');
    let increaseButtons = document.querySelectorAll('.increase');
    let currentQuantity = 0;
    let currentProduct = '';
    let cartItems = localStorage.getItem('productsInCart');
    cartItems = JSON.parse(cartItems);

    for(let i=0; i < increaseButtons.length; i++) {
        decreaseButtons[i].addEventListener('click', () => {
            console.log(cartItems);
            currentQuantity = decreaseButtons[i].parentElement.querySelector('span').textContent;
            console.log(currentQuantity);
            currentProduct = decreaseButtons[i].parentElement.previousElementSibling.previousElementSibling.querySelector('span').textContent.toLocaleLowerCase().replace(/ /g,'').trim();
            console.log(currentProduct);

            if( cartItems[currentProduct].inCart > 1 ) {
                cartItems[currentProduct].inCart -= 1;
                cartNumbers(cartItems[currentProduct], "decrease");
                totalCost(cartItems[currentProduct], "decrease");
                localStorage.setItem('productsInCart', JSON.stringify(cartItems));
                displayCart();
            }
        });

        increaseButtons[i].addEventListener('click', () => {
            console.log(cartItems);
            currentQuantity = increaseButtons[i].parentElement.querySelector('span').textContent;
            console.log(currentQuantity);
            currentProduct = increaseButtons[i].parentElement.previousElementSibling.previousElementSibling.querySelector('span').textContent.toLocaleLowerCase().replace(/ /g,'').trim();
            console.log(currentProduct);

            cartItems[currentProduct].inCart += 1;
            cartNumbers(cartItems[currentProduct]);
            totalCost(cartItems[currentProduct]);
            localStorage.setItem('productsInCart', JSON.stringify(cartItems));
            displayCart();
        });
    }
}

function deleteButtons() {
    let deleteButtons = document.querySelectorAll('.product ion-icon');
    let productNumbers = localStorage.getItem('cartNumbers');
    let cartCost = localStorage.getItem("totalCost");
    let cartItems = localStorage.getItem('productsInCart');
    cartItems = JSON.parse(cartItems);
    let productName;
    console.log(cartItems);

    for(let i=0; i < deleteButtons.length; i++) {
        deleteButtons[i].addEventListener('click', () => {
            productName = deleteButtons[i].parentElement.textContent.toLocaleLowerCase().replace(/ /g,'').trim();
           
            localStorage.setItem('cartNumbers', productNumbers - cartItems[productName].inCart);
            localStorage.setItem('totalCost', cartCost - ( cartItems[productName].price * cartItems[productName].inCart));

            delete cartItems[productName];
            localStorage.setItem('productsInCart', JSON.stringify(cartItems));

            displayCart();
            onLoadCartNumbers();
        })
    }
}
function validateUser(e) {
    const formData = localStorage.getItem('formData');
    if( formData ){
      //console.log('formData exists');
    }else{
      //console.log('formData is not found');
      alert("Dear valued customer, you need to login to add product to the shopping cart.")
      var takeUserFly = confirm("Do you want to login to this website?");
      if (takeUserFly == true) {
        location.href = "login.html";
      }
      else {
        window.location.reload(true);
      }
      
    }
}
onLoadCartNumbers();
displayCart();