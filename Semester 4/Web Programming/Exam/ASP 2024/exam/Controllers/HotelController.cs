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
        private readonly ApplicationDbContext _context;

        public HotelController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: Hotel
        public async Task<IActionResult> Index()
        {
            Registration? currentRegistration = GetCurrentRegistration();

            if (currentRegistration == null)
            {
                return View();
            }
            
            return View(await _context.Hotel.Where(hotel => hotel.Date.Equals(currentRegistration.DesiredDate) &&
                                                               hotel.City.Equals(currentRegistration.CityDestination) &&
                                                               hotel.AvailableRooms > 0)
                .ToListAsync());
        }

        // GET: Hotel/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var hotel = await _context.Hotel
                .FirstOrDefaultAsync(m => m.Id == id);
            if (hotel == null)
            {
                return NotFound();
            }

            return View(hotel);
        }

        // GET: Hotel/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: Hotel/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,Name,Date,City,AvailableRooms")] Hotel hotel)
        {
            if (ModelState.IsValid)
            {
                _context.Add(hotel);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(hotel);
        }

        // GET: Hotel/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var hotel = await _context.Hotel.FindAsync(id);
            if (hotel == null)
            {
                return NotFound();
            }
            return View(hotel);
        }

        // POST: Hotel/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Name,Date,City,AvailableRooms")] Hotel hotel)
        {
            if (id != hotel.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(hotel);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!HotelExists(hotel.Id))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            return View(hotel);
        }

        // GET: Hotel/Delete/5
        public async Task<IActionResult> Reserve(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var hotel = await _context.Hotel
                .FirstOrDefaultAsync(m => m.Id == id);
            if (hotel == null)
            {
                return NotFound();
            }

            return View(hotel);
        }

        // POST: Hotel/Delete/5
        [HttpPost, ActionName("Reserve")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> ReserveConfirmed(int id)
        {
            var hotel = await _context.Hotel.FindAsync(id);
            Registration? currentRegistration = GetCurrentRegistration();
            if (hotel != null && currentRegistration != null)
            {
                hotel.AvailableRooms--;
                this._context.Hotel.Update(hotel);
                Reservations reservations = new Reservations();
                
                reservations.Person = currentRegistration.Name;
                reservations.Type = ReservationType.Hotel;
                reservations.IdReservedResource = id;
                
                this._context.Reservations.Add(reservations);
                
                List<Reservations>? reservationsList = GetReservations();
                if (reservationsList == null)
                {
                    reservationsList = new List<Reservations>();
                }
                
                await _context.SaveChangesAsync();
                
                reservationsList.Add(reservations);
                
                string reservationsJson = JsonConvert.SerializeObject(reservationsList);
                HttpContext.Session.SetString("Reservations", reservationsJson);
            }
            return RedirectToAction(nameof(Index));
        }

        private bool HotelExists(int id)
        {
            return _context.Hotel.Any(e => e.Id == id);
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
