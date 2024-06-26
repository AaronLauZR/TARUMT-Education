<%@ Page Language="C#" MasterPageFile="ClientMasterTailWind.Master" AutoEventWireup="true" CodeBehind="GameLibraryTailWind.aspx.cs" Inherits="Web_Assignment.client.GameLibraryTailWind" %>
<asp:Content ID="Content1" ContentPlaceHolderID="GameLibrary" runat="Server">

    <div class="max-w-screen-lg mx-auto px-4">
        <div class="grid grid-cols-12 text-white mb-10">
            <div class="col-span-6">
                <h3 class="text-3xl font-normal">Game Library</h3>
            </div>
        </div>

        <%--<hr class="mb-4 border-0 border-b-2 border-white opacity-30">--%>

        <div class="grid grid-cols-3 gap-4 mt-10">
            <%--Repeat this card--%>
            <asp:Repeater ID="Repeater1" runat="server">
            <ItemTemplate>
                <div class="col-span-1">
                    <div class="max-w-sm bg-stone-500 border border-gray-200 rounded-lg shadow dark:bg-gray-800 dark:border-gray-700">
                        <%--<a href="#">
                            <img class="rounded-t-lg mx-auto" src="../img/product/dead_space.jpg" alt="" style="height: 200px"/>
                        </a>--%>
                        <asp:Image ID="Image1" runat="server" CssClass="rounded-t-lg mx-auto" style="height: 200px" 
                            ImageUrl='<%#"~/img/product/productCover/"+Eval("image")%>'/>
                        <div class="p-5">
                            <%--<a href="#">
                                <h5 class="mb-2 text-2xl font-bold tracking-tight text-gray-900 dark:text-white">Dead Space III</h5>
                            </a>--%>
                            <asp:label id="lblGameName" runat="server" text='<%#Eval("name") %>' 
                                cssclass="mb-2 text-2xl font-bold tracking-tight text-gray-900 dark:text-white">
                            </asp:label>
                            <p class="mb-3 font-normal text-gray-700 dark:text-gray-400">
                                <%--Description--%>
                                <%#Eval("description")%>
                            </p>
                            <%--<a href="#" class="inline-flex items-center px-3 py-2 text-sm font-medium text-center text-white bg-blue-700 
                                rounded-lg hover:bg-blue-800 focus:ring-4 focus:outline-none focus:ring-blue-300 dark:bg-blue-600 
                                dark:hover:bg-blue-700 dark:focus:ring-blue-800">
                                Review
                                <svg aria-hidden="true" class="w-4 h-4 ml-2 -mr-1" fill="currentColor" viewBox="0 0 20 20" 
                                    xmlns="http://www.w3.org/2000/svg">
                                    <path fill-rule="evenodd" 
                                        d="M10.293 3.293a1 1 0 011.414 0l6 6a1 1 0 010 1.414l-6 6a1 1 0 01-1.414-1.414L14.586 
                                        11H3a1 1 0 110-2h11.586l-4.293-4.293a1 1 0 010-1.414z" clip-rule="evenodd">
                                    </path>
                                </svg>
                            </a>--%>
                            <%--<asp:LinkButton ID="btnReview" runat="server" CssClass="inline-flex items-center px-3 py-2 text-sm font-medium text-center 
                                text-white bg-blue-700 rounded-lg hover:bg-blue-800 focus:ring-4 focus:outline-none focus:ring-blue-300 dark:bg-blue-600 
                                dark:hover:bg-blue-700 dark:focus:ring-blue-800" OnClick="btnReview_Click">
                                Review
                                <svg aria-hidden="true" class="w-4 h-4 ml-2 -mr-1" fill="currentColor" viewBox="0 0 20 20" 
                                    xmlns="http://www.w3.org/2000/svg">
                                    <path fill-rule="evenodd" 
                                        d="M10.293 3.293a1 1 0 011.414 0l6 6a1 1 0 010 1.414l-6 6a1 1 0 01-1.414-1.414L14.586 
                                        11H3a1 1 0 110-2h11.586l-4.293-4.293a1 1 0 010-1.414z" clip-rule="evenodd">
                                    </path>
                                </svg>
                            </asp:LinkButton>--%>
                        </div>
                    </div>
                </div>
            </ItemTemplate>
            </asp:Repeater>
        </div>

        <!----------------- Order Record ----------------->
            <h1 class="text-white text-3xl mb-3">Purchase Game</h1>
            <hr />
            <br />

            <div class="relative overflow-x-auto shadow-md sm:rounded-lg">

                <asp:GridView ID="GridViewOrder" runat="server" AutoGenerateColumns="false" DataKeyNames="orderId" CssClass="table w-full text-sm text-left text-gray-500 dark:text-gray-400 hover:bg-gray-50 dark:hover:bg-gray-600" >
                    <Columns>
                        <asp:BoundField DataField="orderId" HeaderText="Order Id" ReadOnly="True" />
                        <asp:BoundField DataField="orderDate" HeaderText="Order Date" />
                        <asp:BoundField DataField="username" HeaderText="User" />
                    </Columns>
                </asp:GridView>
            
                <asp:Label ID="LabelNoData" runat="server" Text="No order record in database" style="display: none;" CssClass="text-white"></asp:Label>

            </div>

    </div>


</asp:Content>