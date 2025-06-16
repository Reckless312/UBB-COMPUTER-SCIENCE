using System.ComponentModel.DataAnnotations;

namespace exam.Models;

public class Registration
{
    public string Name { get; set; }
    
    [DataType(DataType.Date)]
    public DateTime DesiredDate { get; set; }
    public string CityDestination { get; set; }

}