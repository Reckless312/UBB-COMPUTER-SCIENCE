using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using exam.Data;
using exam.Enum;
using exam.Models;
using Newtonsoft.Json;

namespace exam.Controllers
{
    public class HotelController : Controller
    {
        private readonly ApplicationDbContext databaseContext;

        public HotelController(ApplicationDbContext databaseContext)
        {
            this.databaseContext = databaseContext;
        }
        
        public async Task<IActionResult> Index()
        {
            Registration? currentRegistration = this.GetCurrentRegistration();

            if (currentRegistration == null)
            {
                return View();
            }
            
            return View(await this.databaseContext.Hotel.Where(hotel => hotel.Date.Equals(currentRegistration.DesiredDate) &&
                                                                        hotel.City.Equals(currentRegistration.CityDestination) &&
                                                                        hotel.AvailableRooms > 0)
                .ToListAsync());
        }
        
        public async Task<IActionResult> Reserve(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            Hotel? hotel = await this.databaseContext.Hotel.FirstOrDefaultAsync(m => m.Id == id);
            if (hotel == null)
            {
                return NotFound();
            }

            return View(hotel);
        }
        
        [HttpPost, ActionName("Reserve")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> ReserveConfirmed(int id)
        {
            Hotel? hotel = await this.databaseContext.Hotel.FindAsync(id);
            Registration? currentRegistration = this.GetCurrentRegistration();
            if (hotel != null && currentRegistration != null)
            {
                hotel.AvailableRooms--;
                this.databaseContext.Hotel.Update(hotel);
                Reservations reservations = new Reservations();
                
                reservations.Person = currentRegistration.Name;
                reservations.Type = ReservationType.Hotel;
                reservations.IdReservedResource = id;
                
                this.databaseContext.Reservations.Add(reservations);
                
                List<Reservations>? reservationsList = this.GetReservations();
                if (reservationsList == null)
                {
                    reservationsList = new List<Reservations>();
                }
                
                await databaseContext.SaveChangesAsync();
                
                reservationsList.Add(reservations);
                
                string reservationsJson = JsonConvert.SerializeObject(reservationsList);
                HttpContext.Session.SetString("Reservations", reservationsJson);
            }
            return RedirectToAction(nameof(Index));
        }
        
        public Registration? GetCurrentRegistration()
        {
            string? registrationInStringFormat = HttpContext.Session.GetString("Registration");

            if (registrationInStringFormat == null)
            {
                return null;
            }

            Registration? currentRegistration = JsonConvert.DeserializeObject<Registration>(registrationInStringFormat);

            if (currentRegistration == null)
            {
                return null;
            }

            return currentRegistration;
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
}
