#include<bits/stdc++.h>
using namespace std;

class board
{
    int size;
public:
    board(int s)
    {
        size=s;
    }
    int getsize()
    {
        return size;
    }
};

class player
{
    string name;
    int pos;
    bool won;
public:
    player(string idd)
    {
        name= idd;
        pos=0;
        won=false;
    }
    string getname()
    {
        return name;
    }
    int getpos()
    {
        return pos;
    }
    bool getwinstatus()
    {
        return won;
    }
    void setpos(int x)
    {
        pos= x;
    }
    void setwinstatus(bool w)
    {
        won=w;
    }
};

class dice
{
public:
    int roll_dice()
    {
        return (1+rand()%6);
    }
};

class snake
{
    int start,end;
public:
    snake(int s, int e)
    {
        start =s;
        end=e;
    }
    int getstartpos()
    {
        return start;
    }
    int getendpos()
    {
        return end;
    }
};

class ladder
{
    int start,end;
public:
    ladder(int s, int e)
    {
        start =s;
        end=e;
    }
    int getstartpos()
    {
        return start;
    }
    int getendpos()
    {
        return end;
    }
};


class game
{
    int snakecnt, laddercnt, playercnt;
    int boardsize;
    dice *d=new dice();
    vector<snake *>snakee;
    vector<ladder *>ladders;
    queue<player *>players;
public:
    game(int snk,vector<pair<int,int>>snk1, int ldd, vector<pair<int,int>>ldd1, int plyr, vector<string>plyr1, int bdsize)
    {
        board *bd=new board(bdsize);
        boardsize=bd->getsize();
        for(int i=0;i<snk;i++)
        {
            snake *sk=new snake(snk1[i].first,snk1[i].second);
            snakee.push_back(sk);
        }
        for(int i=0;i<ldd;i++)
        {
            ladder *ld=new ladder(ldd1[i].first,ldd1[i].second);
            ladders.push_back(ld);
        }
        for(int i=0;i<plyr;i++)
        {
            player *pl=new player(plyr1[i]);
            players.push(pl);
        }
    }

    void play()
    {
        while(!players.empty())
        {
            player *p=players.front();
            players.pop();
            int old_pos=p->getpos();
            int dice_val=d->roll_dice();
            int newpos=old_pos+dice_val;
            cout<<"player: "<<p->getname()<<endl;
            if(newpos>boardsize)
            {
                cout<<"moved from "<<old_pos<<" - "<<old_pos<<endl;
                players.push(p);
            }
            else
            {
                cout<<"newpos is: "<<newpos<<endl;
                p->setpos(getfinalpos(newpos));
                int newposition=p->getpos();
                if(newpos==boardsize)
                {
                    cout<<"moved from "<<old_pos<<" - "<<newposition<<endl;
                    cout<<"Winner"<<endl;
                    cout<<endl;
                    p->setwinstatus(true);
                }
                else
                {
                    cout<<"moved from "<<old_pos<<" - "<<newposition<<endl;
                    cout<<endl;
                    players.push(p);
                }
            }
            if(players.size()<2)
                break;
            char c;
            cin>>c;
        }
    }

    int getfinalpos(int newpos)
    {
        snakecnt=snakee.size();
        for(int i=0;i<snakecnt;i++)
        {
            snake *k=snakee[i];
            if(k->getstartpos()==newpos)
            {
                cout<<"bitten by snake. New position:- "<<newpos<<" to "<<k->getendpos()<<endl;
                newpos=k->getendpos();

            }
        }
        laddercnt=ladders.size();
        for(int i=0;i<laddercnt;i++)
        {
            ladder *l=ladders[i];
            if(l->getstartpos()==newpos)
            {
                cout<<"climbed ladder. New position:- "<<newpos<<" to "<<l->getendpos()<<endl;
                newpos=l->getendpos();

            }
        }
        return newpos;
    }
};

int main()
{
    int boardsize, numofsnake, numofladder,playercount;
    vector<pair<int,int>>snake, ladder;
    vector<string>players;
    ifstream file;
    file.open("input.txt");
    if(!file)
    {
        cout<<"\nFile doesn't exist! ";
        exit(1);
    }
    else
    {
        file>>boardsize;
        file>>numofsnake;
        for(int i=0;i<numofsnake;i++)
        {
            int start,endd;
            file>>start;
            file>>endd;
            snake.push_back({start,endd});
        }
        file>>numofladder;
        for(int i=0;i<numofladder;i++)
        {
            int start,endd;
            file>>start;
            file>>endd;
            ladder.push_back({start,endd});
        }
        file>>playercount;
        for(int i=0;i<playercount;i++)
        {
            string str;
            file>>str;
            players.push_back(str);
        }
        file.close();
        cout<<"\nreached file end- \n";
    }
    game *g=new game(numofsnake,snake,numofladder,ladder,playercount,players,boardsize);
    g->play();
    return 0;
}
