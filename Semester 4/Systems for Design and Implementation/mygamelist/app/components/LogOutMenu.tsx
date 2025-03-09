import {
    DropdownMenu,
    DropdownMenuContent, DropdownMenuItem,
    DropdownMenuLabel,
    DropdownMenuSeparator,
    DropdownMenuTrigger
} from "@/app/components/dropdown-menu";
import Image from "next/image";
import {signOut} from "@/auth";
import React from "react";

const LogOutMenu = () => {
    return  <DropdownMenu>
        <DropdownMenuTrigger>
            <Image src="/arrow_drop_down.png" alt="menu drop down" width={30} height={30}></Image>
        </DropdownMenuTrigger>
        <DropdownMenuContent>
            <DropdownMenuLabel>My Account</DropdownMenuLabel>
            <DropdownMenuSeparator />
            <DropdownMenuItem>
                <form action={async () => {
                    "use server";

                    await signOut({redirectTo: "/"});
                }}>
                    <button type="submit">
                        Logout
                    </button>
                </form></DropdownMenuItem>
        </DropdownMenuContent>
    </DropdownMenu>
}

export default LogOutMenu;