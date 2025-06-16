using exam.Data;
using exam.Enum;
using exam.Models;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;

namespace exam.Controllers;

public class RegistrationController : Controller
{
    private readonly ApplicationDbContext _context;

    public RegistrationController(ApplicationDbContext context)
    {
        this._context = context;
    }
    
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

    public IActionResult Clear()
    {
        List<Reservations>? reservations = GetReservations();

        if (reservations == null)
        {
            return View("Index");
        }

        foreach (Reservations reservation in reservations)
        {
            _context.Reservations.Remove(reservation);

            if (reservation.Type == ReservationType.Flight)
            {
                Flights? flight = this._context.Flights.Find(reservation.IdReservedResource);

                if (flight == null)
                {
                    continue;
                }

                flight.AvailableSeats++;

                this._context.Flights.Update(flight);
            }
            else
            {
                Hotel? hotel = this._context.Hotel.Find(reservation.IdReservedResource);

                if (hotel == null)
                {
                    continue;
                }

                hotel.AvailableRooms++;
                
                this._context.Hotel.Update(hotel);
            }
        }
        
        this._context.SaveChanges();
        
        HttpContext.Session.Remove("Reservations");
        HttpContext.Session.Remove("Registration");
        HttpContext.Session.Remove("HasReserved");
        
        return RedirectToAction("Index");
    }
    
    public List<Reservations>? GetReservations()
    {
        string? reservationsInStringFormat = HttpContext.Session.GetString("Reservations");

        if (reservationsInStringFormat == null)
        {
            return null;
        }
            
        List<Reservations>? reservations = JsonConvert.DeserializeObject<List<Reservations>>(reservationsInStringFormat);

        if (reservations == null)
        {
            return null;
        }
            
        return reservations;
    }
}