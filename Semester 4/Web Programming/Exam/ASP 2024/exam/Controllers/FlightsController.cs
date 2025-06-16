using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using exam.Data;
using exam.Enum;
using exam.Models;
using Newtonsoft.Json;

namespace exam.Controllers
{
    public class FlightsController : Controller
    {
        private ApplicationDbContext databaseContext;

        public FlightsController(ApplicationDbContext databaseContext)
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
            
            return View(await this.databaseContext.Flights.Where(flight => flight.Date.Equals(currentRegistration.DesiredDate) &&
                                                               flight.DestinationCity.Equals(currentRegistration.CityDestination) &&
                                                               flight.AvailableSeats > 0).ToListAsync());
        }
        
        public async Task<IActionResult> Reserve(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            Flights? flights = await this.databaseContext.Flights.FirstOrDefaultAsync(m => m.Id == id);
            
            if (flights == null)
            {
                return NotFound();
            }

            return View(flights);
        }
        
        [HttpPost, ActionName("Reserve")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> ReserveConfirmed(int id)
        {
            Flights? flights = await this.databaseContext.Flights.FindAsync(id);
            
            Registration? currentRegistration = this.GetCurrentRegistration();
            
            if (flights != null && currentRegistration != null)
            {
                flights.AvailableSeats--;
                this.databaseContext.Flights.Update(flights);
                
                Reservations reservations = new Reservations();
                reservations.Person = currentRegistration.Name;
                reservations.Type = ReservationType.Flight;
                reservations.IdReservedResource = id;
                
                this.databaseContext.Reservations.Add(reservations);
                
                List<Reservations>? reservationsList = GetReservations();
                if (reservationsList == null)
                {
                    reservationsList = new List<Reservations>();
                }
                
                await this.databaseContext.SaveChangesAsync();
                
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
