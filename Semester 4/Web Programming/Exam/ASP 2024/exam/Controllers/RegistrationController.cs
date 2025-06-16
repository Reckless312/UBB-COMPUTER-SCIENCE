using exam.Models;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;

namespace exam.Controllers;

public class RegistrationController : Controller
{
    public IActionResult Index()
    {
        return View();
    }

    [HttpPost]
    public IActionResult Register(Registration registration)
    {
        string registrationJson = JsonConvert.SerializeObject(registration);
        HttpContext.Session.SetString("Registration", registrationJson);
        
        HttpContext.Session.SetString("HasReserved", "true");
        return RedirectToAction("Index", "Home");
    }
}