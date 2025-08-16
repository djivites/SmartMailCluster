#include "Graph.h"
#include<bits/stdc++.h>
using namespace std;

Graph::Graph(int n)
{
    numUsers=n;
    adjList.resize(n);
    adjMatrix.resize(n,vector<int> (n,0));
    nextEmailId=0;
    nextThreadId=100;
}

int Graph::getNextThreadId()
{
    return nextThreadId++;
}

void Graph::addEdge(int fromEmail,int toEmail,int thread_id)
{
    bool found=false;
    for(auto &edge: adjList[fromEmail])
    {
        if (edge.to==toEmail && edge.thread_id==thread_id)
        {
            edge.weight++;
            found=true;
            break;
        }
    }
    if(!found)
    {
        adjList[fromEmail].push_back({toEmail,1,thread_id});
    }
    adjMatrix[fromEmail][toEmail]+=1;
    
}

void Graph::sendEmail(int from,int to,string subject, string body)
{
    int threadId=getNextThreadId();
    addEdge(from,to,threadId);
    emailStore.push_back({nextEmailId++,from,to,threadId,subject,body});
    cout<<"Email sent.Thread ID:"<<threadId<<"\n";
}

void Graph:: replyEmail(int email_id,int from,int to,string body)
{
    for(auto  email:emailStore)
    {
        if(email.email_id==email_id)
        {
            addEdge(from,to,email.thread_id);

            string reply_subject="RE: "+email.subject;
            emailStore.push_back({
                nextEmailId++,
                from,
                to,
                email.thread_id,
                reply_subject,
                body
            });
        }
        cout << "Reply sent to Email ID " << email_id 
                 << " in Thread " << email.thread_id << "\n";
        return;
    }
    cout << "Error: Email ID " << email_id << " not found.\n";
}

void Graph::forwardEmail(int email_id,int from,int to,string body)
{
    for(auto email:emailStore)
    {
        if(email.email_id==email_id)
        {
            addEdge(from,to,email.thread_id);

            string fwd_sub="FWD: "+email.subject;
            emailStore.push_back({
                nextEmailId++,
                from,
                to,
                email.thread_id,
                fwd_sub,
                body
            });

            cout<<"Email forwarded from Email ID"<<email_id
                <<"in thread"<<email.thread_id<<"\n";
        }

    }
}

void Graph::viewThread(int email_id)
{
    int thread_id=-1;
    
    for(auto email:emailStore)
    {
        if(email.email_id==email_id)
        {
            thread_id=email.thread_id;
            break;
        }
    }

    if(thread_id==-1)
    {
        cout<<"Error: Email id"<<email_id<<"not found\n";
        return ;
    }

    cout<<"Thread"<<thread_id<<":\n";
    for(auto email:emailStore)
    {
        if(email.email_id==thread_id)
        {
            cout<<"Email ID: "<<email.email_id
                << "| From"<<email.from<<"-> To"<<email.to
                << "| Subject :"<<email.subject
                << "| Body "<<email.body<<"\n";
        }
    }
}

// void Graph::BFS(int startEmail)
// {
//     vector<bool> visited(numUsers,false);
//     queue<int> q;
//     visited[startEmail]=false;
//     q.push(startEmail);

//     while(!q.empty())
//     {
//         int email=q.front();
//         q.pop();
//         cout<<email<<" ";

//         for(auto x:adjList[email])
//         {
//             if (!visited[x])
//             {
//                 q.push(x);
//                 visited[x]=true;
//             }
//         }
//     }
//     cout<<"\n";
// }

// void Graph::DFS(int startEmail)
// {
//     vector<bool> visited(numUsers, false);

//     function<void(int)> DFSHELPER = [&](int email) {
//         visited[email] = true;
//         cout << email << " ";

//         for (auto x : adjList[email]) {
//             if (!visited[x]) {
//                 DFSHELPER(x);
//             }
//         }
//     };

//     DFSHELPER(startEmail);
//     cout << "\n";
// }

// void Graph::printAdjMatrix()
// {
//     for (int i = 0; i < numUsers; i++)
//     {
//         for (int j = 0; j < numUsers; j++)
//         {
//             cout << adjMatrix[i][j] << " ";
//         }
//         cout << "\n";
//     }
// }
