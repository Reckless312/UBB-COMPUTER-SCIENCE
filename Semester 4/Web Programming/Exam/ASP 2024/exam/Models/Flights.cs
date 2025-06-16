using System.ComponentModel.DataAnnotations;

namespace exam.Models;

public class Flights
{
    public int Id { get; set; }
    
    [DataType(DataType.Date)]
    public DateOnly Date { get; set; }
    public string DestinationCity { get; set; }
    public int AvailableSeats { get; set; }
}