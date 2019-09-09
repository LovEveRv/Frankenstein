#include "core_processing.h"
#include "neighbor_search.h"

namespace ALG //Default match algorithm
{
    const int INF = 1e9;
    struct Edge
    {
        int from; //from which node
        int to; //point to which node
        int next; //the next edge of this node
        int flow; //the flow on this edge
        int cost; //the cost on this edge
    };
    std::vector<Edge> ed; //T, R, S, T
    std::vector<int> last; //the index of the last edge of this node
    std::vector<int> dis;
    std::vector<int> mark; //current arc optimization
    int S, T, V; //V records the number of nodes
    int Rnum, Tnum; //Number of resource pictures & Number of divides of target pictrue
    int totalflow;
    inline void getmatch(std::vector<std::vector<int>>& Matchinfo)
    {
        for(int i = 0; i < Matchinfo.size(); i++)
        {
            for(int j = 0; j < Matchinfo[i].size(); j++)
            {
                int cur = last[i * Matchinfo[i].size() + j];
                while(cur != -1)
                {
                    if(ed[cur].flow == 0 && ed[cur].to != S)
                    {
                        Matchinfo[i][j] = ed[cur].to - Tnum;
                        break;
                    }
                    cur = ed[cur].next;
                }
            }
        }
    }

    void bfs(int x)
    {
        static std::vector<int> q(V); //queue for bfs
        for(int i = 0; i < V; i++) dis[i] = V + 1; //initialize dis
        dis[x] = 0;
        q[0] = x;
        int l = 0, r = 0;
        while(l <= r)
        {
            int cur = q[l++];
            for(int i = last[cur]; i != -1; i = ed[i].next)
            //search every edge
            {
                if(ed[i].flow > 0 && dis[cur] + 1 < dis[ed[i].to])
                //bfs condition
                {
                    q[++r] = ed[i].to;
                    dis[ed[i].to] = dis[cur] + 1;
                }
            }
        }
        for(int i = 0; i < V; i++) mark[i] = last[i]; //reset mark
    }
    int dfs(int x, int f)
    {
        if(x == T) return f; //arrive at T
        if(f == 0) return f; //prune
        int s = 0;
        for(int i = mark[x]; i != -1; i = ed[i].next)
        //search every edge
        {
            if(dis[ed[i].to] == dis[x] + 1)
            //dfs condition
            {
                int t = dfs(ed[i].to, std::min(f, ed[i].flow));
                //dfs, change f
                s += t;
                f -= t;
                ed[i].flow -= t;
                ed[i ^ 1].flow += t;
                //this is the reverse edge of ed[i]
                //warning: edge index should begin from 0 (using xor)
                mark[x] = i;
                if(f == 0) break;
            }
        }
        return s;
    }
    int rundinic()
    {
        bfs(S);
        return dfs(S, INF);
    }
    void dinic(std::vector<std::vector<int>>& Matchinfo) //Dinic, give an "acceptable" match
    {
        mark = std::vector<int>(V, 0);
        dis = std::vector<int>(V, 0);
        totalflow = 0;

        //msg.print_info("Running: ");
        msg.reset_percentage();

        int t = 0;
        do
        {
            t = rundinic();
            totalflow += t;
            msg.show_percentage(totalflow * 100 / Tnum);
        }
        while(t > 0);

        getmatch(Matchinfo);

        msg.show_percentage(100);
        //msg.print_info("\nComplete.\n");
    }


    std::vector<int> DIS;
    std::vector<bool> VIS;
    int aug(int x, int flow)
    {
        VIS[x] = 1;
        if(x == T)
        {
            totalflow += flow;
            msg.show_percentage(totalflow * 100 / Tnum);
            return flow;
        }
        int tp;
        for(int i = last[x]; i != -1; i = ed[i].next)
        {
            if(ed[i].flow > 0 && !VIS[ed[i].to] && DIS[x] + ed[i].cost == DIS[ed[i].to])
            {
                tp = aug(ed[i].to, std::min(flow, ed[i].flow));
                if(tp > 0)
                {
                    ed[i].flow -= tp;
                    ed[i ^ 1].flow += tp;
                    return tp;
                }
            }
        }
        return 0;
    }
    bool mdf()
    {
        if(VIS[T] == 1) return true;
        int z = INF;
        for(int i = 0; i < ed.size(); i++)
        {
            if(ed[i].flow > 0 && VIS[ed[i].from] && !VIS[ed[i].to]) z = std::min(z, DIS[ed[i].from] + ed[i].cost - DIS[ed[i].to]);
        }
        if(z == INF) return false;
        for(int i = 0; i < V; i++) if(VIS[i]) DIS[i] -= z;
        return true;
    }
    void zkw(std::vector<std::vector<int>>& Matchinfo) //Zkw-costflow, give a "best" match
    {
        totalflow = 0;
        DIS = std::vector<int>(V, 0);
        VIS = std::vector<bool>(V, 0);

        //msg.print_info("Running: ");
        msg.reset_percentage();

        do
        {
            do
            {
                for(int i = 0; i < V; i++) VIS[i] = 0;
            }
            while(aug(S, INF));
        }
        while(mdf());

        getmatch(Matchinfo);

        msg.show_percentage(100);
        //msg.print_info("\nComplete.\n");
    }
}

inline int getdis(Element& p1, Element& p2, double dist_punish, int threshold)
{
    assert(p1.dim() == p2.dim());
    int ans = 0;
    for(int i = 0; i < p1.dim(); i++)
    {
        int dif = p1[i] - p2[i];
        if(abs(dif) > threshold) return -1;
        ans += dif * dif;
    }
    return pow(ans, dist_punish);
}
inline void addedge(int from, int to, int flow, int cost)
{
    static ALG::Edge e;
    
    e.from = from;
    e.to = to;
    e.flow = flow;
    e.cost = cost;
    e.next = ALG::last[from];
    ALG::last[from] = ALG::ed.size();
    ALG::ed.push_back(e);
    
    e.from = to;
    e.to = from;
    e.flow = 0;
    e.cost = 0 - cost;
    e.next = ALG::last[to];
    ALG::last[to] = ALG::ed.size();
    ALG::ed.push_back(e);
}

void Core_Process_Module::Build_Graph(int opt)
{
    using std::vector;
    ALG::Tnum = Input_Data->Target_Image_Info.size() * Input_Data->Target_Image_Info[0].size();
    ALG::Rnum = Input_Data->Resource_Image_Info.size();
    ALG::V = ALG::Rnum + ALG::Tnum + 2;
    ALG::T = ALG::V - 1;
    ALG::S = ALG::V - 2;
    ALG::last = std::vector<int>(ALG::V, -1);

    //msg.print_info("Building graph: ");
    msg.reset_percentage();

    NeighborSearcher<256> fd_engine(Input_Data->Resource_Image_Info[0].dim(), threshold);
    for(Element &cur : Input_Data->Resource_Image_Info)
    {
        fd_engine.add_point(cur);
    }
    int Tid=0;
    for(auto &i: Input_Data->Target_Image_Info)
        for(Element &j : i)
        {
            addedge(ALG::S, Tid, 1, 1);
            vector<int> candidate_id = fd_engine.search_neighbor(j);
            std::vector<std::pair<int, int>> candidate;
            for(int k : candidate_id) candidate.emplace_back(getdis(j, Input_Data->Resource_Image_Info[k], dist_punish, threshold), k);
            if(opt) std::sort(candidate.begin(), candidate.end());
            for(int k = candidate.size() - 1; k >= 0; k--) addedge(Tid, candidate[k].second+ALG::Tnum, 1, candidate[k].first);
            msg.show_percentage(Tid * 100 / (ALG::Tnum - 1));
            ++Tid;
        }    
    for(int k = 0; k < Input_Data->Resource_Image_Info.size(); k++)
    {
        int Rid = ALG::Tnum + k;
        addedge(Rid, ALG::T, 1, 1);
    }

    msg.show_percentage(100);
    //msg.print_info("\nComplete.\n");
}

Datapack_Matchinfo* Core_Process_Module::execute(int alg_selection)
{
    delete myMatch;
    myMatch = new Datapack_Matchinfo();
    myMatch->Match_Info = std::vector<std::vector<int>>(Input_Data->Target_Image_Info.size(), std::vector<int>(Input_Data->Target_Image_Info[0].size(), -1));
    
    switch(alg_selection)
    {
        case 1:
            Build_Graph(1);
            ALG::dinic(myMatch->Match_Info);
            break;
        case 2:
            Build_Graph();
            ALG::zkw(myMatch->Match_Info);
            break;
    }

    return myMatch;
}
