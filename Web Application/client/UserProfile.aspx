<%@ Page Language="C#" MasterPageFile="ClientMaster.Master" AutoEventWireup="true" CodeBehind="UserProfile.aspx.cs" Inherits="Web_Assignment.client.UserProfile" %>

<asp:Content ID="Content1" ContentPlaceHolderID="userprofile" runat="Server">

    <div>
        <p class="maintitle">Account Settings</p>
    </div>

    <div>
        <p class="subtitle">Account Information</p>
    </div>

    <div class="border">
        <p class="label">
            Account ID<br />
            <asp:Label ID="AccountID" runat="server" class="id">UserID</asp:Label>
        </p>
    </div>

    <div>
        <p class="maintitle">Personal Information</p>
    </div>

    <div>
        <p class="subtitle">Personal Details</p>
        <p class="des">Manage your personal information and region's details.</p>
    </div>

    <div class="border">
        <p class="label">
            Username<br />
            <asp:Label ID="Label1" runat="server" class="text"></asp:Label>
        </p>
        <p class="label">
            Email<br />
            <asp:Label ID="Label2" runat="server" class="text"></asp:Label>
        </p>
        <p class="label">
            Region<br />
            <asp:Label ID="Label3" runat="server" class="text"></asp:Label>
        </p>
    </div>

    <div>
        <p class="subtitle">Password</p>
        <p class="des">
            For your security propose, we highly recommend that you choose a unique password that you don't use for any other account. 
            Your password must contain at least 8 characters
        </p>
    </div>

    <div class="border">
        <p class="label">
            Current Password :&nbsp;&nbsp; &nbsp;
            <asp:TextBox ID="currentpass" runat="server" class="passwordtext" TextMode="Password"></asp:TextBox>
        &nbsp;</p>
        <p class="label">
            New Password :&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp; <asp:TextBox ID="newpass" runat="server" class="passwordtext" TextMode="Password"></asp:TextBox>
        &nbsp;<%--<asp:RequiredFieldValidator ID="RequiredFieldValidator1" class="errormessage2" runat="server" ControlToValidate="newpass" ErrorMessage="New password is required."></asp:RequiredFieldValidator>--%>
        </p>
        <p class="label">
            Confirm Password :&nbsp;&nbsp;&nbsp;
            <asp:TextBox ID="confirmpass" runat="server" class="passwordtext" TextMode="Password" ValidationExpression="\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*"></asp:TextBox>
        &nbsp;<asp:RegularExpressionValidator ID="RegularExpressionValidator1" class="errormessage2" runat="server" ControlToValidate="newpass" ErrorMessage="Password contain minimum 8 characters, incldue 1 letter and 1 number." ValidationExpression="^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$"></asp:RegularExpressionValidator>
        </p>
        <p><asp:Label class="errormessage" ID="errormessage" runat="server"></asp:Label></p>
        <asp:Button ID="changepassword" runat="server" Text="Save Changes" class="btnsubmit" Style="background-color: #9F76AE; color: white;" OnClick="changepassword_Click" />
    </div>

    <div class="maintitle">
        <p>Account Deletion</p>
    </div>

    <div class="border">
        <p class="delsubtitle">Delete Your Account</p>
        <table>
            <tr class="deldes">
                <td>Click "DELETE ACCOUNT" to permanently deleting your Galaxy Games account including all personal 
                        information, games purchases, game progress, account history and other related information. 
                        Once your Galaxy Games account is deleted, your won't able to request any refund or return.</td>
                <td>
                    <asp:Button ID="delete" runat="server" Text="DELETE ACCOUNT" class="delbtn" OnClick="delete_Click" />
                </td>
            </tr>
        </table>
    </div>
    <br />
    <br />
</asp:Content>
