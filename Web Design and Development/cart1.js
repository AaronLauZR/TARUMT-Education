let carts = document.querySelectorAll('.add-cart');

let products = [ 
    {
        name: "Men's Basketball Jackete",
        tag: "men'sbasketballjackete",
        price: 139,
        inCart: 0
    },
    {
        name: "Dri-FIT Rayguns",
        tag: "dri-fitrayguns",
        price: 269,
        inCart: 0
    },
    {
        name: "NBA Jersey",
        tag: "nbajersey",
        price: 495,
        inCart: 0
    },
    {
        name: "Men's NBA Shorts",
        tag: "men'snbashorts",
        price: 149,
        inCart: 0
    },
    {
        name: "2019 Flash Men's Basketball Shoes",
        tag: "2019flashmen'sbasketballshoes",
        price: 440,
        inCart: 0
    },
    {
        name: "Taichi Flash 2019 Men's Basketball Shoes",
        tag: "taichiflash2019men'sbasketballshoes",
        price: 520,
        inCart: 0
    },
    {
        name: "Mens Breathe Combat high-top basketball shoe",
        tag: "mensbreathecombathigh-topbasketballshoe",
        price: 300,
        inCart: 0
    },
    {
        name: "Speed Shadow Combat Basketball Shoes",
        tag: "speedshadowcombatbasketballshoes",
        price: 420,
        inCart: 0
    },
    {
        name: "NBA SINGLE BALL BASKETBALL BAG",
        tag: "nbasingleballbasketballbag",
        price: 40,
        inCart: 0
    },
    {
        name: "TNBA AUTHENTIC SERIES INDOOR BASKETBALL",
        tag: "tnbaauthenticseriesindoorbasketball",
        price: 520,
        inCart: 0
    },
    {
        name: "COACHES DRY ERASE BOARD",
        tag: "coachesdryeraseboard",
        price: 80,
        inCart: 0
    },
    {
        name: "Los Angeles Lakers Stance HWC Gradient Sock - Yellow - Mens",
        tag: "losangeleslakersstancehwcgradientsock-yellow-mens",
        price: 88,
        inCart: 0
    }

];

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
                <ion-icon name="trash-outline"></ion-icon>
                <img src="./image/All_product/${item.tag}.jpg" />
                <span class="sm-hide">${item.name}</span>
            </div>
            <div class="price sm-hide">RM${item.price}.00</div>
            <div class="quantity">
                <ion-icon class="increase" name="caret-down-outline"></ion-icon>
                    <span>${item.inCart}</span>
                <ion-icon class="decrease" name="caret-up-outline"></ion-icon>
            </div>
            <div class="total">RM${item.inCart * item.price}.00</div>`;
        });

        productContainer.innerHTML += `
            <div class="basketTotalContainer">
                <h4 class="basketTotalTitle">Basket Total</h4>
                <h4 class="basketTotal">RM${cart}.00</h4>
            </div>`

        deleteButtons();
        manageQuantity();
    }
}

function manageQuantity() {
    let decreaseButtons = document.querySelectorAll('.increase');
    let increaseButtons = document.querySelectorAll('.decrease');
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