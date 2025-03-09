import React from 'react'
import Link from "next/link";
import Image from "next/image";
import {auth, signIn, signOut} from "@/auth";

import {
    DropdownMenu,
    DropdownMenuContent,
    DropdownMenuItem,
    DropdownMenuLabel,
    DropdownMenuSeparator,
    DropdownMenuTrigger,
} from "@/app/components/dropdown-menu"

const Navbar = async () => {
    const session = await auth();

    return (
        <header className="bg-black px-4">
            <nav className="flex items-center justify-between">
                <Link href="/">
                    <Image src="/logo.png" alt="logo" width={144} height={30} />
                </Link>
                <div className="flex items-center justify-between text-white">
                    {session && session.user ? (
                        <>
                            <div className="flex items-center justify-between px-2">
                                <DropdownMenu>
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
                                <span>{session?.user?.name}</span>
                                <DropdownMenu>
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
                                <Image src={session?.user?.image || "/logo.png"} alt="profile picture" width={30} height={30}></Image>
                            </div>
                        </>
                    ) : (
                        <form action={async () => {
                            "use server";

                            await signIn('github');
                        }}>
                            <button className="text-white bg-green-400 px-8 py-0.1 rounded-2xl cursor-pointer" type="submit">
                                Login
                            </button>
                        </form>
                    )}
                </div>
            </nav>
        </header>
    )
}

export default Navbar;