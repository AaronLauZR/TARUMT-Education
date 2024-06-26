<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Register.aspx.cs" Inherits="Web_Assignment.client.Register" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <link rel="stylesheet" href="../css/account.css" />
    <title></title>
    <style type="text/css">
        .auto-style2 {
            width: 49%;
        }

        .auto-style6 {
            text-align: left;
        }

        .auto-style7 {
            height: 27px;
            text-align: left;
        }

        .auto-style8 {
            height: 27px;
            text-align: right;
            width: 277px;
        }

        .auto-style9 {
            text-align: right;
            width: 277px;
        }

        .auto-style11 {
            text-align: right;
            width: 277px;
            height: 50px;
        }

        .auto-style12 {
            text-align: left;
            height: 50px;
        }

        .auto-style13 {
            height: 27px;
        }

        .auto-style14 {
            height: 35px;
            text-align: right;
            width: 277px;
        }

        .auto-style15 {
            height: 35px;
            text-align: left;
        }
    </style>
</head>

<body>
    <form id="form1" runat="server">

        <img src="../img/logo.png" alt="LOGO" class="logo" />

        <img src="../img/account/ufo-flying.png" alt="UFO" class="ufo" />

        <br />
        <br />
        <br />
        <img src="../img/account/galaxy.png" alt="GALAXY" class="topic" />

        <br />
        <br />
        <br />
        <table class="auto-style2">
            <tr>
                <td class="auto-style8" id="label">Username :&nbsp;&nbsp; </td>
                <td class="auto-style7">
                    <asp:TextBox ID="usernametxt" runat="server" class="box"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td class="auto-style8">&nbsp;</td>
                <td class="auto-style7">
                    <asp:RequiredFieldValidator class="errormessage" ID="RequiredFieldValidator1" runat="server" ControlToValidate="usernametxt" ErrorMessage="Username is required." ForeColor="Red"></asp:RequiredFieldValidator>
                    <br />
                    <asp:Label class="errormessage" ID="userexist" runat="server"></asp:Label>
                </td>
            </tr>
            <tr>
                <td class="auto-style8" id="label">Email :&nbsp;&nbsp; </td>
                <td class="auto-style7">
                    <asp:TextBox ID="emailtxt" runat="server" class="box" placeholder="abc@gmail.com"></asp:TextBox>
                    <br />
                </td>
            </tr>
            <tr>
                <td class="auto-style8">
                    <br />
                </td>
                <td class="auto-style7">
                    <asp:RequiredFieldValidator class="errormessage" ID="RequiredFieldValidator6" runat="server" ControlToValidate="emailtxt" ErrorMessage="Email is required." ForeColor="Red"></asp:RequiredFieldValidator>
                    <br />
                    <asp:RegularExpressionValidator class="errormessage" ID="RegularExpressionValidator1" runat="server" ControlToValidate="emailtxt" ErrorMessage="RegularExpressionValidator" ForeColor="Red" ValidationExpression="\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*">Please enter valid email.</asp:RegularExpressionValidator>
                </td>
            </tr>
            <tr>
                <td class="auto-style11" id="label">Password :&nbsp;&nbsp; </td>
                <td class="auto-style12" id="passwordformat">
                    <asp:TextBox ID="passwordtxt" runat="server" class="box" placeholder="abcd1234" OnTextChanged="passwordtxt_TextChanged" TextMode="Password"></asp:TextBox>
                    &nbsp;<br />
                </td>
            </tr>
            <tr>
                <td class="auto-style14"></td>
                <td class="auto-style15" id="passwordformat">Password contain minimum 8 characters, incldue 1 letter and 1 number.<br />
                    <asp:RequiredFieldValidator class="errormessage" ID="RequiredFieldValidator5" runat="server" ControlToValidate="passwordtxt" ErrorMessage="Password is required." ForeColor="Red"></asp:RequiredFieldValidator>
                    <br />
                    <asp:RegularExpressionValidator class="errormessage" ID="RegularExpressionValidator2" runat="server" ControlToValidate="passwordtxt" ErrorMessage="Please enter valid password format." ForeColor="Red" ValidationExpression="^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$"></asp:RegularExpressionValidator>
                </td>
            </tr>
            <tr>
                <td class="auto-style9" id="label">Confirm Password :&nbsp;&nbsp; </td>
                <td class="auto-style6">
                    <asp:TextBox ID="confirmpassword" runat="server" class="box" TextMode="Password"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td class="auto-style8"></td>
                <td class="auto-style7">
                    <asp:CompareValidator class="errormessage" ID="CompareValidator1" runat="server" ControlToCompare="passwordtxt" ControlToValidate="confirmpassword" ErrorMessage="CompareValidator" ForeColor="Red">Password must be same</asp:CompareValidator>
                </td>
            </tr>
            <tr>
                <td class="auto-style9" id="label">Region :&nbsp;&nbsp; </td>
                <td class="auto-style6">
                    <asp:DropDownList class="regiondropdown" ID="regiontxt" runat="server" Width="180px" OnSelectedIndexChanged="DropDownList1_SelectedIndexChanged">
                        <asp:ListItem>Malaysia</asp:ListItem>
                        <asp:ListItem>India</asp:ListItem>
                        <asp:ListItem>Japan</asp:ListItem>
                        <asp:ListItem>Korea</asp:ListItem>
                        <asp:ListItem>China</asp:ListItem>
                        <asp:ListItem>Singapore</asp:ListItem>
                        <asp:ListItem>Thailand</asp:ListItem>
                        <asp:ListItem>Others</asp:ListItem>
                    </asp:DropDownList>
                </td>
            </tr>
            <tr>
                <td class="auto-style9">&nbsp;</td>
                <td class="auto-style6">
                    <asp:RequiredFieldValidator class="errormessage" ID="RequiredFieldValidator4" runat="server" ErrorMessage="Please select a region" ForeColor="Red" ControlToValidate="regiontxt"></asp:RequiredFieldValidator>
                </td>
            </tr>
            <tr>
                <td class="auto-style8">&nbsp;</td>
                <td class="auto-style13">
                    <asp:Button ID="register" runat="server" Text="Register" class="submitbtn" OnClick="register_Click1" />

                </td>
            </tr>
        </table>

        <br />
        <br />
        <p class="account">
            Already have account? 
        <asp:HyperLink ID="login" runat="server" class="hyper" NavigateUrl="~/client/Login.aspx">Log In</asp:HyperLink>
        </p>
    </form>
</body>
</html>
