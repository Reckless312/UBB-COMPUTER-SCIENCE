using exam.Enum;

namespace exam.Models;

public class Reservations
{
    public int Id { get; set; }
    public string Person { get; set; }
    public ReservationType Type { get; set; }
    public int IdReservedResource { get; set; }
}