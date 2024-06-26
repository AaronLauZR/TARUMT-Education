<%@ Page Language="C#" MasterPageFile="ClientMasterTailWind.Master" AutoEventWireup="true" CodeBehind="AboutUs.aspx.cs" Inherits="Web_Assignment.client.AboutUs" %>

<asp:Content ID="Content1" ContentPlaceHolderID="aboutus" runat="Server">

    <article>
        <h1 class="abtitle">About GALAXY</h1>
        <p class="abtext">
            Welcome to <strong>GALAXY</strong> online game selling website! 
            Trying to find the cheapest and integrated games? 
            Looking for the best gaming experience? 
            Finding for the best and most suitable game styles for yourself? 
            Here GALAXY, is the best platform for you to find your lovely game with the most suitable price!
        </p>
        <p class="abtext">
            GALAXY launched in 2023, it is a platform tailored for the region, providing customers 
            the best gaming experience through providing perfect games performance and fulfillment support.
        </p>
        <p class="abtext">
            Our platform is user-friendly, easy to navigate, and designed to make your shopping experience as hassle-free as possible. 
            With our intuitive search and filtering tools, you can quickly find the games you want and browse through reviews 
            and ratings from other gamers to make an informed decision.
        </p>
        <p class="abtext">
            We all believe that gaming should be enjoyable and relaxable. This is the wish of all 3
            staff in GALAXT aspires to deliver on the platform every single day.
        </p>
        <p class="abtext">
            So why wait? Start browsing our extensive catalog of games today and find your next favorite title!
        </p>

        <div id="flex">
            <div class="about-card">
                <h2 class="cardtopic">Our Purpose</h2>
                <div>
                    <img src="../img/aboutus/purpose.png" alt="USER EXPERINCE" width="386" height="265">
                    <div >
                        <h3>User Experience</h3>
                    </div>
                </div>
                <p>
                    We believe that the games categories and  paltform performance will provide the 
                    best user experince to everyone.
                </p>
            </div>

            <div class="about-card">
                <h2 class="cardtopic">Our Target</h2>
                <div>
                    <img src="../img/aboutus/target.png" alt="RELAXABLE" width="386" height="265">
                    <div>
                        <h3>Relaxable</h3>
                    </div>
                </div>
                <p>
                    We hope that everyone who using our platform will be able to have the best gaming
                experience and felt relax in their stressful period.
                </p>
            </div>

            <div class="about-card">
                <h2 class="cardtopic">Our Personality</h2>
                <div id="polaroid">
                    <img src="../img/aboutus/personality.png" alt="FRIENDLY" width="386" height="265">
                    <div id="container">
                        <h3>Friendly</h3>
                    </div>
                </div>
                <p>
                    We will serve every customer that comes from a different country with different skin colour 
                who has a mind to buy the games with the most friendly service.
                </p>
            </div>
        </div>

        <br />
        <br />
        <br />
        <h1 class="abteamtitle">Our Team</h1>

        <div class="team">
            <div class="card mb-3" style="max-width: 540px;">
                <div class="row g-0">
                    <div class="col-md-4">
                        <img src="../img/aboutus/zhongren.png" class="img-fluid rounded-start" alt="LAU ZHONG REN">
                    </div>
                    <div class="col-md-8">
                        <div class="card-body">
                            <h5 class="card-title">Mr. LAU ZHONG REN</h5>
                            <p class="card-text">
                                Dear valued customers, thank you for choosing us  for purchasing games. 
            We look forward to continuing to serve you with exceptional service.
                            </p>
                            <p class="card-text"><small class="text-body-secondary"><strong>Email: </strong>lauzr-wm21@student.tarc.edu.my</small></p>
                        </div>
                    </div>
                </div>
            </div>

            <div class="card mb-3" style="max-width: 540px;">
                <div class="row g-0">
                    <div class="col-md-4">
                        <img src="../img/aboutus/andrew.png" class="img-fluid rounded-start" alt="ANDREW HEW JUN SHENG">
                    </div>
                    <div class="col-md-8">
                        <div class="card-body">
                            <h5 class="card-title">Mr. ANDREW HEW JUN SHENG</h5>
                            <p class="card-text">
                                We're committed to delivering the best possible experience for you, and we're constantly 
            working to improve our platform and services.
                            </p>
                            <p class="card-text"><small class="text-body-secondary"><strong>Email: </strong>andrewhjs-wm21@student.tarc.edu.my</small></p>
                        </div>
                    </div>
                </div>
            </div>
            <div class="card mb-3" style="max-width: 540px;">
                <div class="row g-0">
                    <div class="col-md-4">
                        <img src="../img/aboutus/hinyong.png" class="img-fluid rounded-start" alt="VOON HIN YONG">
                    </div>
                    <div class="col-md-8">
                        <div class="card-body">
                            <h5 class="card-title">Mr. VOON HIN YONG</h5>
                            <p class="card-text">
                                I wanted to take a moment to extend a heartfelt thank you for your choice. 
            Thanks for your business and for being part of our community.
                            </p>
                            <p class="card-text"><small class="text-body-secondary"><strong>Email: </strong>voonhy-wp20@student.tarc.edu.my</small></p>
                        </div>
                    </div>
                </div>
            </div>
            <div class="card mb-3" style="max-width: 540px;">
                <div class="row g-0">
                    <div class="col-md-4">
                        <img src="../img/aboutus/tzenyang.png" class="img-fluid rounded-start" alt="CHEONG TZEN YANG">
                    </div>
                    <div class="col-md-8">
                        <div class="card-body">
                            <h5 class="card-title">Mr. CHEONG TZEN YANG</h5>
                            <p class="card-text">
                                We are grateful for your support and trust in our platform, 
            and we take pride in providing you with the best possible experience. Thank you for you supporting.
                            </p>
                            <p class="card-text"><small class="text-body-secondary"><strong>Email: </strong>cheongty-wp20@student.tarc.edu.my</small></p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </article>
</asp:Content>
