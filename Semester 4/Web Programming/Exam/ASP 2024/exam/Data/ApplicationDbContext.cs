using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using exam.Models;

namespace exam.Data;

public class ApplicationDbContext : IdentityDbContext
{
    public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
        : base(options)
    {
    }

public DbSet<exam.Models.Flights> Flights { get; set; } = default!;

public DbSet<exam.Models.Hotel> Hotel { get; set; } = default!;

public DbSet<exam.Models.Reservations> Reservations { get; set; } = default!;
}