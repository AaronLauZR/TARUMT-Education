<%@ Page Language="C#" MasterPageFile="AdminMaster.Master" AutoEventWireup="true" CodeBehind="Dashboard.aspx.cs" Inherits="Web_Assignment.admin.Dashboard" %>



<asp:Content ID="Content1" ContentPlaceHolderID="Dashboard" runat="Server">
    <html xmlns="http://www.w3.org/1999/xhtml">

    <title>Dashboard</title>
    <body>


        <div class="container mx-auto px-5 p-4 bg-zinc-900">

            <div class="flex flex-wrap">
                <div class="w-full md:w-1/2 xl:w-1/2 p-6">
                    <!------------ Order ------------>
                    <div class="bg-gradient-to-b from-green-200 to-green-100 border-b-4 border-green-600 rounded-lg shadow-xl p-5">
                        <div class="flex flex-row items-center">
                            <div class="flex-shrink pr-4">
                                <div class="rounded-full p-5 bg-green-600"><i class="fa fa-wallet fa-2x fa-inverse"></i></div>
                            </div>
                            <div class="flex-1 text-right md:text-center">
                                <h2 class="font-bold uppercase text-gray-600">Total Order</h2>
                                <asp:Label ID="totalOrder" runat="server" CssClass="font-bold text-3xl"></asp:Label>
                            </div>
                        </div>
                    </div>
                    <!--------------------------------->
                </div>

                <div class="w-full md:w-1/2 xl:w-1/2 p-6">
                   <!------------ Product ------------>
                    <div class="bg-gradient-to-b from-blue-200 to-blue-100 border-b-4 border-blue-500 rounded-lg shadow-xl p-5">
                        <div class="flex flex-row items-center">
                            <div class="flex-shrink pr-4">
                                <div class="rounded-full p-5 bg-blue-600"><i class="fas fa-inbox fa-2x fa-inverse"></i></div>
                            </div>
                            <div class="flex-1 text-right md:text-center">
                                <h2 class="font-bold uppercase text-gray-600">Total Product</h2>
                                <asp:Label ID="totalProduct" runat="server" CssClass="font-bold text-3xl"></asp:Label>
                            </div>
                        </div>
                    </div>
                    <!--------------------------------->
                 </div>

                <div class="w-full md:w-1/2 xl:w-1/2 p-6">
                    <!------------ User ------------>
                    <div class="bg-gradient-to-b from-pink-200 to-pink-100 border-b-4 border-pink-500 rounded-lg shadow-xl p-5">
                        <div class="flex flex-row items-center">
                            <div class="flex-shrink pr-4">
                                <div class="rounded-full p-5 bg-pink-600"><i class="fas fa-users fa-2x fa-inverse"></i></div>
                            </div>
                            <div class="flex-1 text-right md:text-center">
                                <h2 class="font-bold uppercase text-gray-600">Total Users</h2>
                                <asp:Label ID="totalUser" runat="server" CssClass="font-bold text-3xl"></asp:Label>
                            </div>
                        </div>
                    </div>
                    <!--------------------------------->
                </div>

                <div class="w-full md:w-1/2 xl:w-1/2 p-6">
                    <!------------ Role ------------>
                    <div class="bg-gradient-to-b from-yellow-200 to-yellow-100 border-b-4 border-yellow-600 rounded-lg shadow-xl p-5">
                        <div class="flex flex-row items-center">
                            <div class="flex-shrink pr-4">
                                <div class="rounded-full p-5 bg-yellow-600"><i class="fas fa-user-plus fa-2x fa-inverse"></i></div>
                            </div>
                            <div class="flex-1 text-right md:text-center">
                                <h2 class="font-bold uppercase text-gray-600">Total Role</h2>
                                <asp:Label ID="totalRole" runat="server" CssClass="font-bold text-3xl"></asp:Label>
                            </div>
                        </div>
                    </div>
                    <!--------------------------------->
                </div>

                
            </div>

            <br />

            <!----------------- Order Record ----------------->
            <h1 class="text-white text-3xl mb-3">Order Record</h1>
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

    </body>
    </html>
</asp:Content>
