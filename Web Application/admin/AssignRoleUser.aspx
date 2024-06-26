<%@ Page Language="C#" MasterPageFile="AdminMaster.Master" AutoEventWireup="true" CodeBehind="AssignRoleUser.aspx.cs" Inherits="Web_Assignment.admin.UpdateRole" %>

<asp:Content ID="Content1" ContentPlaceHolderID="AssignRoleUser" runat="Server">
    
    <div class="container mx-auto px-5">

        <h1 class="text-white text-3xl mb-3">Assign Role User</h1>
        <hr />

        <br />

        <!---------- Assign Role Form ---------->
        <div class="text-white">

            <!----- User DropDownList ----->
            <div class="mb-6">
                <label class="block mb-2 text-sm font-medium" runat="server">User</label>         
                <asp:DropDownList ID="ddlUser" runat="server" CssClass="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500">
                    <asp:ListItem>--- Select User ---</asp:ListItem>
                </asp:DropDownList>
                <!--- Genre Dropdown Validator --->
                <asp:RequiredFieldValidator ID="RequiredFieldValidatorUser" runat="server" ErrorMessage="User must be chosen" InitialValue="--- Select User ---" ControlToValidate="ddlUser" ForeColor="#FF3300"></asp:RequiredFieldValidator>
            </div>

            <!----- Role DropDownList ----->
            <div class="mb-6">
                <label class="block mb-2 text-sm font-medium" runat="server">Role</label>
                <asp:DropDownList ID="ddlRole" runat="server" CssClass="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500">
                    <asp:ListItem>--- Select Role ---</asp:ListItem>
                </asp:DropDownList>
                 <!--- System Dropdown Validator --->
                <asp:RequiredFieldValidator ID="RequiredFieldValidatorRole" runat="server" ErrorMessage="Role must be chosen" InitialValue="--- Select Role ---" ControlToValidate="ddlRole" ForeColor="#FF3300"></asp:RequiredFieldValidator>
            </div>

            <asp:Button ID="btnAssignRole" runat="server" Text="Assign" class="text-white bg-blue-700 hover:bg-blue-800 focus:ring-4 focus:outline-none focus:ring-blue-300 font-medium rounded-lg text-sm w-full sm:w-auto px-5 py-2.5 text-center dark:bg-blue-600 dark:hover:bg-blue-700 dark:focus:ring-blue-800" OnClick="btnAssignRole_Click" />
        </div>


        <!----- Display User Data ----->
        <br /><br />
        <h1 class="text-white text-3xl mb-3">Display User</h1>
        <hr />
        <br />

        <div class="relative overflow-x-auto shadow-md sm:rounded-lg">

            <asp:GridView ID="GridViewUser" runat="server" AutoGenerateColumns="False" DataKeyNames="userId" CssClass="table w-full text-sm text-left text-gray-500 dark:text-gray-400 hover:bg-gray-50 dark:hover:bg-gray-600" >
                <Columns>
                    <asp:BoundField DataField="userId" HeaderText="Id" ReadOnly="True" />
                    <asp:BoundField DataField="username" HeaderText="Username" />
                    <asp:BoundField DataField="email" HeaderText="Email" />
                    <asp:BoundField DataField="roleName" HeaderText="Role" />
                    <asp:BoundField DataField="region" HeaderText="Region" />

                </Columns>
            </asp:GridView>
            
            <asp:Label ID="LabelNoData" runat="server" Text="No user in database" style="display: none;" CssClass="text-white"></asp:Label>

        </div>


    </div>


</asp:Content>
