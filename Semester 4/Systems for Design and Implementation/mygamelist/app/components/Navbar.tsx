import React from 'react'
import Image from "next/image";
import {auth, signIn} from "@/auth";
import OthersMenu from "@/app/components/OthersMenu";
import LogOutMenu from "@/app/components/LogOutMenu";
import Link from "next/link";

const Navbar = async () => {
    const session = await auth();

    return (
        <header className="bg-black px-4">
            <nav className="flex items-center justify-between ml-14 mr-14">
                <Link href="/">
                    <Image src="/logo.png" alt="logo" width={144} height={30} />
                </Link>
                <div className="flex items-center justify-between text-white">
                    {session && session.user ? (
                        <>
                            <div className="flex items-center justify-between px-2">
                                <OthersMenu/>
                                <span>{session?.user?.name}</span>
                                <LogOutMenu/>
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