import {
    DropdownMenu,
    DropdownMenuContent, DropdownMenuItem,
    DropdownMenuLabel,
    DropdownMenuSeparator,
    DropdownMenuTrigger
} from "@/app/components/dropdown-menu";
import Image from "next/image";
import React from "react";

const OthersMenu = () => {
     return   <DropdownMenu>
            <DropdownMenuTrigger>
                <Image src="/menu.png" alt="main menu" width={30} height={30}></Image>
            </DropdownMenuTrigger>
            <DropdownMenuContent>
                <DropdownMenuLabel>Others</DropdownMenuLabel>
                <DropdownMenuSeparator />
                <DropdownMenuItem>
                    My List
                </DropdownMenuItem>
            </DropdownMenuContent>
        </DropdownMenu>
}

export default OthersMenu;