<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="ClientMasterTailWind.Master" CodeBehind="Home.aspx.cs" Inherits="Web_Assignment.client.Home" %>

<asp:Content ContentPlaceHolderID="home" runat="server">

    
    <div class="hero min-h-screen" style="background-image: url(../img/bg-image.jpg);">
        <div class="hero-overlay bg-opacity-60"></div>
        <div class="hero-content text-center text-neutral-content">
            <div class="max-w-md">
                <h1 class="mb-5 text-5xl font-bold">Hello there</h1>
                <p class="mb-5">Our game selling website offers a diverse range of the latest video games across all platforms at competitive prices, providing a convenient and hassle-free shopping experience for gamers.</p>
                <button class="btn btn-primary">Get Started</button>
            </div>
        </div>
    </div>


    <br />
    <h1 class="text-3xl" id="Browse">&nbsp;&nbsp; Hot Games ></h1>
    

    <div>
        <div class="carousel carousel-center max-w-full p-6 space-x-7 bg-neutral rounded-box bg-zinc-900">
            
            <!---------- Product Item Repeater ---------->
            <asp:Repeater ID="RepeaterDisplayProduct" runat="server" OnItemCommand="RepeaterDisplayProduct_ItemCommand">
                <ItemTemplate>
                    <div class="carousel-item">
                        <div class="card w-96 glass">
                            <figure>
                                <!--<img src="../img/mh.jpg" style="width: 300px; height: 300px;" />-->
                                <asp:Image ID="Image1" runat="server" style="width: 300px; height: 300px;" alt='<%#Eval("name") %>' ImageUrl='<%#"~/img/product/productCover/"+Eval("image")%>'  />
                            </figure>
                            <div class="card-body text-white">
                                <h2 class="card-title"><%#Eval("name") %></h2>
                                <p><%#Eval("description") %></p>
                                <div class="card-actions justify-end">
                                    <asp:LinkButton ID="LinkButton1" runat="server" class="btn btn-primary m-4" PostBackUrl='<%# "~/client/Product.aspx?id=" + HttpUtility.UrlEncode(Eval("productId").ToString()) %>'><%#Eval("price") %></asp:LinkButton>
                                </div>
                            </div>
                        </div>
                    </div>
                </ItemTemplate>
            </asp:Repeater>

            

        </div>

     </div>

</asp:Content>