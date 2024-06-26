const signUp = e => {
    let userid = document.getElementById('userid').value,
        email = document.getElementById('email').value,
        pwd = document.getElementById('pwd').value;

    let formData = JSON.parse(localStorage.getItem('formData')) || [];

    let exist = formData.length && 
        JSON.parse(localStorage.getItem('formData')).some(data => 
            data.userid == userid && 
            data.email == email
        );

    if(!exist){
        var namesArr = [];
        formData.push({ userid, email, pwd });
        namesArr.push(userid);
        localStorage.setItem('formData', JSON.stringify(formData));
        localStorage.setItem('names',JSON.stringify(namesArr));
        document.querySelector('form').reset();
        document.getElementById('userid').focus();
        alert("Account Created.\n\nPlease Sign In using the link below.");
    }
    else{
        alert("Sorry, duplicate account found!!\nYou have already signed up");
    }
    e.preventDefault();
}

function signIn(e) {
    let userid = document.getElementById('userid').value, pwd = document.getElementById('pwd').value;
    let formData = JSON.parse(localStorage.getItem('formData')) || [];
    let exist = formData.length && 
    JSON.parse(localStorage.getItem('formData')).some(data => data.userid == userid && data.pwd == pwd);

    if(!exist){
        alert("Incorrect login credentials");
    }
    else{
        location.href = "/";
    }
    e.preventDefault();
}

function myFunction() {
    var x = document.getElementById("pwd")
    var y = document.getElementById("hide1")
    var z = document.getElementById("hide2")

    if (x.type === 'password') {
        x.type = "text";
        y.style.display = "block";
        z.style.display = "none";
    }
    else {
        x.type = "password";
        y.style.display = "none";
        z.style.display = "block";
    }
}


