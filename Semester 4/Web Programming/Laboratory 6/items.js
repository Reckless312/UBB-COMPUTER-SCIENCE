let data;
function initializeComponents(url, showItems)
{
    try
    {
        fetch(url,
            {
                method: "GET",
                headers: {"Content-Type": "application/json"}
            })
            .then(response =>
            {
                if (!response.ok)
                {
                    throw new Error("We didn't receive a status 200 from the server!");
                }
                return response.json();
            })
            .then(items => {
                data = items;
                createPagesButtons(showItems, data);
            })
    }
    catch (error)
    {
        console.log(error)
    }
}