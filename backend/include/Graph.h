#ifndef GRAPH_H
#define GRAPH_H

#include<bits/stdc++.h>
using namespace std;

struct EmailEdge{
    int to;
    int weight ;
    int thread_id;
};

struct Email{
    int email_id;
    int from;
    int to;
    int thread_id;
    string subject;
    string body;
};

class Graph{
    private:
    vector<vector<EmailEdge>> adjList;
    vector<vector<int>> adjMatrix;
    vector<Email> emailStore;
    int numUsers;
    int nextEmailId;
    int nextThreadId;

    public:
    Graph(int n);
    void addEdge(int fromEmail,int toEmail,int threadId);
    vector<int> getNeighbours(int emialId);
    void BFS(int startEmail);
    void DFS(int startEmail);

    void sendEmail(int from ,int to ,string subject, string body);
    void replyEmail(int email_id,int from,int to,string body);
    void forwardEmail(int email_id,int from,int to,string body);
    void viewThread(int email_id);
    void viewThreadDFS(int start_mail_id);
    void dfsHelper(int email_id,vector<bool> visited);

    //void printAdjMatrix();

    void viewGraph(int email_id);
    void viewThread(int thread_id);
    int getNextThreadId();
};

#endif