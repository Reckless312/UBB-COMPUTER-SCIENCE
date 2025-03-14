export type Games = {
    id: number;
    name: string;
    status: 'plan-to-play' | 'playing' | 'completed';
    score: 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10;
    startedDate: Date;
    finishedDate: Date;
};