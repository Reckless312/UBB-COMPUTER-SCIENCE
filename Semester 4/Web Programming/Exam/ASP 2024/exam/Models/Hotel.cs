using System.ComponentModel.DataAnnotations;

namespace exam.Models;

public class Hotel
{
    public int Id { get; set; }
    public string Name { get; set; }
    
    [DataType(DataType.Date)]
    public DateTime Date { get; set; }
    public string City { get; set; }
    public int AvailableRooms { get; set; }
}