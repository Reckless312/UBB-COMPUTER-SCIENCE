import Image from "next/image";
import clsx from 'clsx';
import {auth} from "@/auth";

export default function Home() {
    return (
    <>
        <div className="bg-black h-full">
            <Image className="absolute text-whiteflex space-x-10 ml-20 mr-20" src="/steam.png" alt="background" height={767} width={1245}>

            </Image>
        </div>
    </>
  );
}
