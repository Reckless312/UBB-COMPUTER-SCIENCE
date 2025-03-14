import PageHead from "@/app/components/PageHead";
import '@/app/globals.css'
import { inter } from '@/app/ui/fonts';
import Footer from "@/app/components/Footer";
import PagesNavigation from "@/app/components/PagesNavigation";
import React from "react";
import {auth} from "@/auth";

export default async function Layout({ children }: Readonly<{ children: React.ReactNode }>) {
    const session = await auth();

    return (
        <html lang="en">
            <body>
                <main className={`${inter.className} antialiased min-h-screen bg-black`}>
                    <PageHead session={session ? { user: { name: session.user?.name ?? undefined, image: session.user?.image ?? undefined } } : null}/>
                    <PagesNavigation />
                    {children}
                    <Footer />
                </main>
            </body>
        </html>
    )
}