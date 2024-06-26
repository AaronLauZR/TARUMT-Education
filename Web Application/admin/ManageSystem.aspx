<%@ Page Language="C#" MasterPageFile="AdminMaster.Master" AutoEventWireup="true" CodeBehind="ManageSystem.aspx.cs" Inherits="Web_Assignment.admin.AddSystem" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ManageSystem" runat="Server">
    
    <div class="container mx-auto px-5">

        <h1 class="text-white text-3xl mb-3">Add System</h1>
        <hr />

        <br />

        <!---------- Add System Requirements Form ---------->
        <div class="text-white">

            <!----- Operating System ----->
            <div class="mb-6">
                <label class="block mb-2 text-sm font-medium" runat="server">Operating System</label>
                <asp:TextBox ID="txtOperatingSystem" runat="server" class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500" placeholder="e.g. Window OS"></asp:TextBox>
                <!--- Operating System Validator --->
                <asp:RequiredFieldValidator ID="RequiredFieldValidatorOS" ValidationGroup="systemValidatorGroup" runat="server" ErrorMessage="Operating System is required" ControlToValidate="txtOperatingSystem" ForeColor="#FF3300"></asp:RequiredFieldValidator>    
            </div>

            <!----- Processor ----->
            <div class="mb-6">
                <label class="block mb-2 text-sm font-medium" runat="server">Processor</label>
                <asp:TextBox ID="txtProcessor" runat="server" class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500" placeholder="e.g. Intel Core i5-10400"></asp:TextBox>
                <!--- Processor Validator --->
                <asp:RequiredFieldValidator ID="RequiredFieldValidatorProcessor" ValidationGroup="systemValidatorGroup" runat="server" ErrorMessage="Processor is required" ControlToValidate="txtProcessor" ForeColor="#FF3300"></asp:RequiredFieldValidator>
            </div>

            <!----- Storage ----->
            <div class="mb-6">
                <label class="block mb-2 text-sm font-medium" runat="server">Storage</label>
                <asp:TextBox ID="txtStorage" runat="server" class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:text-white dark:focus:ring-blue-500 dark:focus:border-blue-500" placeholder="e.g. 10GB"></asp:TextBox>
                <!--- Product Name Validator --->
                <asp:RequiredFieldValidator ID="RequiredFieldValidatorStorage" ValidationGroup="systemValidatorGroup" runat="server" ErrorMessage="Storage is required" ControlToValidate="txtStorage" ForeColor="#FF3300"></asp:RequiredFieldValidator>
            </div>

            <br />

            <asp:Button ID="btnAddSystem" ValidationGroup="systemValidatorGroup" CauseValidation="true" runat="server" Text="Add" class="text-white bg-blue-700 hover:bg-blue-800 focus:ring-4 focus:outline-none focus:ring-blue-300 font-medium rounded-lg text-sm w-full sm:w-auto px-5 py-2.5 text-center dark:bg-blue-600 dark:hover:bg-blue-700 dark:focus:ring-blue-800" OnClick="btnAddSystem_Click" />
        </div>

        <!----- Data Output ----->
        <!----- Display Genre Data ----->
        <br /><br />
        <h1 class="text-white text-3xl mb-3">Manage System</h1>
        <hr />
        <br />

        <div class="relative overflow-x-auto shadow-md sm:rounded-lg">

            <asp:GridView ID="GridViewSystem" runat="server" AutoGenerateColumns="false" DataKeyNames="systemId" CssClass="table w-full text-sm text-left text-gray-500 dark:text-gray-400 hover:bg-gray-50 dark:hover:bg-gray-600" OnRowCancelingEdit="GridViewSystem_RowCancelingEdit" OnRowDeleting="GridViewSystem_RowDeleting" OnRowEditing="GridViewSystem_RowEditing" OnRowUpdating="GridViewSystem_RowUpdating" >
                <Columns>
                    <asp:BoundField DataField="systemId" HeaderText="Id" ReadOnly="True" />
                    <asp:BoundField DataField="os" HeaderText="Operating System" />
                    <asp:BoundField DataField="processor" HeaderText="Processor" />
                    <asp:BoundField DataField="storage" HeaderText="Storage" />

                    <asp:CommandField ShowEditButton="True" ControlStyle-CssClass="btn btn-success btn-sm rounded-0 border-green-500 hover:border-green-500 bg-white hover:bg-green-500" />
                    <asp:CommandField ShowDeleteButton="True" ControlStyle-CssClass="btn btn-damage btn-sm rounded-0 border-red-500 hover:border-red-500 bg-white hover:bg-red-500 text-black" />
                </Columns>
            </asp:GridView>
            
            <asp:Label ID="LabelNoData" runat="server" Text="No system in database" style="display: none;" CssClass="text-white"></asp:Label>

        </div>


    </div>

</asp:Content>
