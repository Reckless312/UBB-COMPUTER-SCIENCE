import Navbar from "@/app/components/Navbar";
import '@/app/globals.css'
import { inter } from '@/app/ui/fonts';
import Footer from "@/app/components/Footer";
import PagesNavigation from "@/app/components/PagesNavigation";

export default function Layout({ children }: Readonly<{ children: React.ReactNode }>) {
    return (
        <main className={`${inter.className} antialiased min-h-screen bg-black`}>
            <Navbar />
            <PagesNavigation />
            {children}
            <Footer />
        </main>
    )
}