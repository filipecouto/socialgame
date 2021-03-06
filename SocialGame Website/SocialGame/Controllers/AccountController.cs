﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Transactions;
using System.Web;
using System.Web.Mvc;
using System.Web.Security;
using DotNetOpenAuth.AspNet;
using Microsoft.Web.WebPages.OAuth;
using WebMatrix.WebData;
using SocialGame.Filters;
using SocialGame.Models;
using SocialGame.ComLayer;
using SocialGame.CustomAttributes;

namespace SocialGame.Controllers
{
    public class AccountController : Controller
    {
        private ComUsers comUsers = new ComUsers();
        private HttpSession session = new HttpSession();
        private IntExtension intExt = new IntExtension();

        //
        // GET: /Account/Login

        [AllowAnonymous]
        public ActionResult Login(string returnUrl)
        {
            ViewBag.ReturnUrl = returnUrl;
            return View();
        }

        //
        // POST: /Account/Login

        [HttpPost]
        [AllowAnonymous]
        [ValidateAntiForgeryToken]
        public ActionResult Login(LoginModel model, string returnUrl)
        {
            //WebSecurity.Login(model.Email, model.Password, persistCookie: model.RememberMe)
            if (ModelState.IsValid && comUsers.Login(model.Email, model.Password))
            {
                return RedirectToLocal(returnUrl);
            }

            // If we got this far, something failed, redisplay form
            ModelState.AddModelError("", "The email or password provided is incorrect.");
            return View(model);
        }

        //
        // POST: /Account/LogOff

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult LogOff()
        {
            comUsers.Logout();

            return RedirectToAction("Index", "Home");
        }

        //
        // GET: /Account/Register

        [AllowAnonymous]
        public ActionResult Register()
        {
            return View();
        }

        //
        // POST: /Account/Register

        [HttpPost]
        [AllowAnonymous]
        [ValidateAntiForgeryToken]
        public ActionResult Register(RegisterModel model)
        {
            if (ModelState.IsValid)
            {
                // Attempt to register the user
                try
                {
                    comUsers.CreateUserAndAccount(model.UserName, model.Email, model.Password);
                    comUsers.Login(model.Email, model.Password);
                    return RedirectToAction("Index", "Profile");
                }
                catch (MembershipCreateUserException e)
                {
                    ModelState.AddModelError("", ErrorCodeToString(e.StatusCode));
                }
            }

            // If we got this far, something failed, redisplay form
            return View(model);
        }

        //
        // POST: /Account/Disassociate

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Disassociate(string provider, string providerUserId)
        {
            string ownerAccount = OAuthWebSecurity.GetUserName(provider, providerUserId);
            ManageMessageId? message = null;

            // Only disassociate the account if the currently logged in user is the owner
            if (ownerAccount == User.Identity.Name)
            {
                // Use a transaction to prevent the user from deleting their last login credential
                using (var scope = new TransactionScope(TransactionScopeOption.Required, new TransactionOptions { IsolationLevel = IsolationLevel.Serializable }))
                {
                    bool hasLocalAccount = OAuthWebSecurity.HasLocalAccount(WebSecurity.GetUserId(User.Identity.Name));
                    if (hasLocalAccount || OAuthWebSecurity.GetAccountsFromUserName(User.Identity.Name).Count > 1)
                    {
                        OAuthWebSecurity.DeleteAccount(provider, providerUserId);
                        scope.Complete();
                        message = ManageMessageId.RemoveLoginSuccess;
                    }
                }
            }

            return RedirectToAction("Manage", new { Message = message });
        }

        // GET: /Account/Manage
        //[SGAuthorize(Types = new[] { 1, 2 })]

        [SGAuthorize]
        public ActionResult Manage()
        {
            
            //ViewBag.HasLocalPassword = OAuthWebSecurity.HasLocalAccount(WebSecurity.GetUserId(User.Identity.Name));
            //ViewBag.ReturnUrl = Url.Action("Manage");

            ViewBag.Moods = comUsers.GetMoodsSelectList();
            ViewBag.PictureLink = comUsers.GetUserInformation().picture;
            ViewBag.Tags = comUsers.GetUserTags();
            return View();
        }

        // POST: /Account/ChangePassword

        [SGAuthorize]
        public ActionResult ChangePassword(LocalPasswordModel model)
        {
            /*bool hasLocalAccount = OAuthWebSecurity.HasLocalAccount(WebSecurity.GetUserId(User.Identity.Name));
            ViewBag.HasLocalPassword = hasLocalAccount;*/
            //ViewBag.ReturnUrl = Url.Action("Manage");
            /*if (hasLocalAccount)
            {*/
                if (ModelState.IsValid)
                {
                    // ChangePassword will throw an exception rather than return false in certain failure scenarios.
                    bool changePasswordSucceeded = true;
                    try
                    {
                        changePasswordSucceeded = comUsers.ChangePassword(model.OldPassword, model.NewPassword);
                    }
                    catch (Exception)
                    {
                        changePasswordSucceeded = false;
                    }

                    if (changePasswordSucceeded)
                    {
                        return Json(new { state = "success", message = MessageIdToString(ManageMessageId.ChangePasswordSuccess) });
                    }
                    else
                    {
                        return Json(new { state = "error", message = MessageIdToString(ManageMessageId.PasswordError) });
                    }
                }
            /*}
            else
            {
                // User does not have a local password so remove any validation errors caused by a missing
                // OldPassword field
                ModelState state = ModelState["OldPassword"];
                if (state != null)
                {
                    state.Errors.Clear();
                }

                if (ModelState.IsValid)
                {
                    try
                    {
                        WebSecurity.CreateAccount(User.Identity.Name, model.NewPassword);
                        return RedirectToAction("Manage", new { Message = ManageMessageId.SetPasswordSuccess });
                    }
                    catch (Exception)
                    {
                        ModelState.AddModelError("", String.Format("Unable to create local account. An account with the name \"{0}\" may already exist.", User.Identity.Name));
                    }
                }
            }*/

            // If we got this far, something failed, redisplay form
            return RedirectToAction("Manage");
        }

        [SGAuthorize]
        public ActionResult ChangeUserName(User model)
        {
            if (ModelState.IsValid)
            {
                // ChangeUserName will throw an exception rather than return false in certain failure scenarios.
                bool changeUserNameSucceeded = true;
                try
                {
                    if (model.username == session.readFromSession("UserName"))
                    {
                        return Json(new { state = "error", message = MessageIdToString(ManageMessageId.NoChanges) });
                    }
                    else if (model.username == "" || model.username == null)
                    {
                        return Json(new { state = "error", message = MessageIdToString(ManageMessageId.BlankField) });
                    }

                    changeUserNameSucceeded = comUsers.ChangeUserName(model.username);
                    if (changeUserNameSucceeded)
                    {
                        return Json(new { state = "success", message = MessageIdToString(ManageMessageId.ChangeUserNameSuccess) });
                    }
                    else
                    {
                        return Json(new { state = "error", message = MessageIdToString(ManageMessageId.PasswordError) });
                    }
                }
                catch (Exception)
                {
                    changeUserNameSucceeded = false;
                }
            }

            // If we got this far, something failed, redisplay form
            return RedirectToAction("Manage");
        }

        [SGAuthorize]
        public ActionResult ChangeMood(string moodId)
        {
            if (ModelState.IsValid)
            {
                // ChangeMood will throw an exception rather than return false in certain failure scenarios.
                bool changeMoodSucceeded = true;
                try
                {
                    changeMoodSucceeded = comUsers.ChangeUserMood(int.Parse(moodId));
                    if (changeMoodSucceeded)
                    {
                        return Json(new { state = "success", message = MessageIdToString(ManageMessageId.ChangeMoodSuccess) });
                    }
                    else
                    {
                        return Json(new { state = "error", message = MessageIdToString(ManageMessageId.NoChanges) });
                    }
                }
                catch (Exception)
                {
                    changeMoodSucceeded = false;
                }
            }

            // If we got this far, something failed, redisplay form
            return RedirectToAction("Manage");
        }

        [SGAuthorize]
        public ActionResult ChangePicture(User model)
        {
            if (ModelState.IsValid)
            {
                // ChangePicture will throw an exception rather than return false in certain failure scenarios.
                bool changePictureSucceeded = true;
                try
                {
                    changePictureSucceeded = comUsers.ChangeUserPicture(model.picture);
                    if (changePictureSucceeded)
                    {
                        return Json(new { state = "success", message = MessageIdToString(ManageMessageId.ChangePictureSuccess) });
                    }
                    else
                    {
                        return Json(new { state = "error", message = MessageIdToString(ManageMessageId.NoChanges) });
                    }
                }
                catch (Exception)
                {
                    changePictureSucceeded = false;
                }
            }

            // If we got this far, something failed, redisplay form
            return RedirectToAction("Manage");
        }

        [SGAuthorize]
        public ActionResult ChangeTags(string tags)
        {
            if (ModelState.IsValid)
            {
                // ChangePicture will throw an exception rather than return false in certain failure scenarios.
                bool changeTagsSucceeded = true;
                try
                {
                    changeTagsSucceeded = comUsers.ChangeUserTags(tags);
                    if (changeTagsSucceeded)
                    {
                        return Json(new { state = "success", message = MessageIdToString(ManageMessageId.ChangeTagsSuccess) });
                    }
                    else
                    {
                        return Json(new { state = "error", message = MessageIdToString(ManageMessageId.NoChanges) });
                    }
                }
                catch (Exception)
                {
                    changeTagsSucceeded = false;
                }
            }

            // If we got this far, something failed, redisplay form
            return RedirectToAction("Manage");
        }

        //
        // POST: /Account/ExternalLogin

        [HttpPost]
        [AllowAnonymous]
        [ValidateAntiForgeryToken]
        public ActionResult ExternalLogin(string provider, string returnUrl)
        {
            return new ExternalLoginResult(provider, Url.Action("ExternalLoginCallback", new { ReturnUrl = returnUrl }));
        }

        //
        // GET: /Account/ExternalLoginCallback

        [AllowAnonymous]
        public ActionResult ExternalLoginCallback(string returnUrl)
        {
            AuthenticationResult result = OAuthWebSecurity.VerifyAuthentication(Url.Action("ExternalLoginCallback", new { ReturnUrl = returnUrl }));
            if (!result.IsSuccessful)
            {
                return RedirectToAction("ExternalLoginFailure");
            }

            if (OAuthWebSecurity.Login(result.Provider, result.ProviderUserId, createPersistentCookie: false))
            {
                return RedirectToLocal(returnUrl);
            }

            if (User.Identity.IsAuthenticated)
            {
                // If the current user is logged in add the new account
                OAuthWebSecurity.CreateOrUpdateAccount(result.Provider, result.ProviderUserId, User.Identity.Name);
                return RedirectToLocal(returnUrl);
            }
            else
            {
                // User is new, ask for their desired membership name
                string loginData = OAuthWebSecurity.SerializeProviderUserId(result.Provider, result.ProviderUserId);
                ViewBag.ProviderDisplayName = OAuthWebSecurity.GetOAuthClientData(result.Provider).DisplayName;
                ViewBag.ReturnUrl = returnUrl;
                return View("ExternalLoginConfirmation", new RegisterExternalLoginModel { UserName = result.UserName, ExternalLoginData = loginData });
            }
        }

        //
        // POST: /Account/ExternalLoginConfirmation

        [HttpPost]
        [AllowAnonymous]
        [ValidateAntiForgeryToken]
        public ActionResult ExternalLoginConfirmation(RegisterExternalLoginModel model, string returnUrl)
        {
            string provider = null;
            string providerUserId = null;

            if (User.Identity.IsAuthenticated || !OAuthWebSecurity.TryDeserializeProviderUserId(model.ExternalLoginData, out provider, out providerUserId))
            {
                return RedirectToAction("Manage");
            }

            if (ModelState.IsValid)
            {
                // Insert a new user into the database
                using (UsersContext db = new UsersContext())
                {
                    UserProfile user = db.UserProfiles.FirstOrDefault(u => u.UserName.ToLower() == model.UserName.ToLower());
                    // Check if user already exists
                    if (user == null)
                    {
                        // Insert name into the profile table
                        db.UserProfiles.Add(new UserProfile { UserName = model.UserName });
                        db.SaveChanges();

                        OAuthWebSecurity.CreateOrUpdateAccount(provider, providerUserId, model.UserName);
                        OAuthWebSecurity.Login(provider, providerUserId, createPersistentCookie: false);

                        return RedirectToLocal(returnUrl);
                    }
                    else
                    {
                        ModelState.AddModelError("UserName", "User name already exists. Please enter a different user name.");
                    }
                }
            }

            ViewBag.ProviderDisplayName = OAuthWebSecurity.GetOAuthClientData(provider).DisplayName;
            ViewBag.ReturnUrl = returnUrl;
            return View(model);
        }

        //
        // GET: /Account/ExternalLoginFailure

        [AllowAnonymous]
        public ActionResult ExternalLoginFailure()
        {
            return View();
        }

        [AllowAnonymous]
        [ChildActionOnly]
        public ActionResult ExternalLoginsList(string returnUrl)
        {
            ViewBag.ReturnUrl = returnUrl;
            return PartialView("_ExternalLoginsListPartial", OAuthWebSecurity.RegisteredClientData);
        }

        [ChildActionOnly]
        public ActionResult RemoveExternalLogins()
        {
            //ICollection<OAuthAccount> accounts = OAuthWebSecurity.GetAccountsFromUserName(User.Identity.Name);
            List<ExternalLogin> externalLogins = new List<ExternalLogin>();
            /*foreach (OAuthAccount account in accounts)
            {
                AuthenticationClientData clientData = OAuthWebSecurity.GetOAuthClientData(account.Provider);

                externalLogins.Add(new ExternalLogin
                {
                    Provider = account.Provider,
                    ProviderDisplayName = clientData.DisplayName,
                    ProviderUserId = account.ProviderUserId,
                });
            }

            ViewBag.ShowRemoveButton = externalLogins.Count > 1 || OAuthWebSecurity.HasLocalAccount(WebSecurity.GetUserId(User.Identity.Name));*/
            return PartialView("_RemoveExternalLoginsPartial", externalLogins);
        }

        #region Helpers
        private ActionResult RedirectToLocal(string returnUrl)
        {
            if (Url.IsLocalUrl(returnUrl))
            {
                return Redirect(returnUrl);
            }
            else
            {
                return RedirectToAction("Index", "Home");
            }
        }

        public enum ManageMessageId
        {
            ChangePasswordSuccess,
            SetPasswordSuccess,
            RemoveLoginSuccess,
            PasswordError,
            NoChanges,
            BlankField,
            ChangeUserNameSuccess,
            ChangeMoodSuccess,
            ChangePictureSuccess,
            ChangeTagsSuccess,
        }

        public string MessageIdToString(ManageMessageId? message)
        {
            return 
                message == ManageMessageId.ChangePasswordSuccess ? "Your password has been changed."
                : message == ManageMessageId.SetPasswordSuccess ? "Your password has been set."
                : message == ManageMessageId.RemoveLoginSuccess ? "The external login was removed."
                : message == ManageMessageId.PasswordError ? "The current password is incorrect or the new password is invalid."
                : message == ManageMessageId.NoChanges ? "No changes made."
                : message == ManageMessageId.BlankField ? "Cannot update blank field."
                : message == ManageMessageId.ChangeUserNameSuccess ? "Your name has been changed."
                : message == ManageMessageId.ChangeMoodSuccess ? "Your mood has been changed."
                : message == ManageMessageId.ChangePictureSuccess ? "Your picture has been changed."
                : message == ManageMessageId.ChangeTagsSuccess ? "Your tags have been changed."
                : "";
        }

        internal class ExternalLoginResult : ActionResult
        {
            public ExternalLoginResult(string provider, string returnUrl)
            {
                Provider = provider;
                ReturnUrl = returnUrl;
            }

            public string Provider { get; private set; }
            public string ReturnUrl { get; private set; }

            public override void ExecuteResult(ControllerContext context)
            {
                OAuthWebSecurity.RequestAuthentication(Provider, ReturnUrl);
            }
        }

        private static string ErrorCodeToString(MembershipCreateStatus createStatus)
        {
            // See http://go.microsoft.com/fwlink/?LinkID=177550 for
            // a full list of status codes.
            switch (createStatus)
            {
                case MembershipCreateStatus.DuplicateUserName:
                    return "User name already exists. Please enter a different user name.";

                case MembershipCreateStatus.DuplicateEmail:
                    return "A user name for that e-mail address already exists. Please enter a different e-mail address.";

                case MembershipCreateStatus.InvalidPassword:
                    return "The password provided is invalid. Please enter a valid password value.";

                case MembershipCreateStatus.InvalidEmail:
                    return "The e-mail address provided is invalid. Please check the value and try again.";

                case MembershipCreateStatus.InvalidAnswer:
                    return "The password retrieval answer provided is invalid. Please check the value and try again.";

                case MembershipCreateStatus.InvalidQuestion:
                    return "The password retrieval question provided is invalid. Please check the value and try again.";

                case MembershipCreateStatus.InvalidUserName:
                    return "The user name provided is invalid. Please check the value and try again.";

                case MembershipCreateStatus.ProviderError:
                    return "The authentication provider returned an error. Please verify your entry and try again. If the problem persists, please contact your system administrator.";

                case MembershipCreateStatus.UserRejected:
                    return "The user creation request has been canceled. Please verify your entry and try again. If the problem persists, please contact your system administrator.";

                default:
                    return "An unknown error occurred. Please verify your entry and try again. If the problem persists, please contact your system administrator.";
            }
        }
        #endregion
    }
}
