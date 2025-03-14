import {
    DropdownMenu,
    DropdownMenuContent, DropdownMenuItem,
    DropdownMenuLabel,
    DropdownMenuSeparator,
    DropdownMenuTrigger
} from "@/app/components/dropdown-menu";
import React from "react";

const MenuComponent = (props: {image: React.ReactNode, label: string; option: React.ReactNode}) => {
     return   <DropdownMenu>
            <DropdownMenuTrigger>
                {props.image}
            </DropdownMenuTrigger>
            <DropdownMenuContent>
                <DropdownMenuLabel>{props.label}</DropdownMenuLabel>
                <DropdownMenuSeparator />
                <DropdownMenuItem>{props.option}</DropdownMenuItem>
            </DropdownMenuContent>
        </DropdownMenu>
}

export default MenuComponent;