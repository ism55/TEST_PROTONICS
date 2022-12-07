#include <algorithm>
#include <iostream>
#include <thread>
#include <queue>
#include <random>
#include <time.h>
#include <atomic>
#include <chrono>
#include <condition_variable>

using namespace std;

std::string date_to_str(time_t t);
class LimitedQueue
{

private:
    int _max = 100;

public:
    queue<vector<char>> q;
    void addToQueue(vector<char> v)
    {
        if (q.size() > _max)
        {
            q.pop();
        }
        else
        {
            q.push(v);
        };
    }

    void removeOfQueue()
    {
        q.pop();
    }
};

class IModule
{
public:
    virtual void Send(mutex &mu, queue<vector<char>> &q, condition_variable &cv) = 0;
    virtual void Receive(mutex &mu, queue<vector<char>> &q, condition_variable &cv) = 0;
    virtual void print_array(vector<char> array) = 0;
};

class ModuleOne : public IModule
{
private:
    vector<char> _generate_array()
    {
        random_device _rd;
        mt19937 gen(_rd());
        uniform_int_distribution<> bytes(0, 255);
        uniform_int_distribution<> array_len(1, 100);

        vector<char> generated;
        generated.clear();
        for (int i = 0; i < array_len(gen); i++)
        {
            generated.push_back(bytes(gen));
        }

        return generated;
    }

    void _print_array(vector<char> array)
    {
        for (int i = 0; i < array.size(); i++)
        {
            cout << array[i] << ',';
        }
        cout << endl;
    }

public:
    LimitedQueue _queue;
    mutex tMut;
    std::condition_variable tCV;
    vector<char> generated;
    void Send(mutex &mu, queue<vector<char>> &q, condition_variable &cv)
    {
        lock_guard<mutex> lg(mu);
        // cout << "modulo1_thread" << endl;
        int k;
        while (k < 100000)
        {
            generated = _generate_array();
            q.push(generated);
            k++;
        }

        cv.notify_one();
    }
    void Receive(mutex &mu, queue<vector<char>> &q, condition_variable &cv)
    {
        lock_guard<mutex> lg(mu);
        cv.notify_one();
    }

    void print_array(vector<char> array) { _print_array(array); }
};

class ModuleTwo : public IModule
{
private:
    vector<char> match = {'a', 'b'};

    void _print_array(vector<char> array)
    {
        for (int i = 0; i < array.size(); i++)
        {
            cout << array[i] << ',';
        }
        cout << endl;
    }

    void _Receive(mutex &mu, queue<vector<char>> &q, condition_variable &cv)
    {
        unique_lock<mutex> ul(mu);
        // cout << "modulo2_thread Receive" << endl;

        cv.wait(ul, [&] { return (q.empty()) ? false : true; });
        while (!q.empty())
        {
            if (!q.front().empty())
            {
                auto it = search(q.front().begin(), q.front().end(), match.begin(), match.end());

                if (it != q.front().end())
                {
                    // cout << "Match found at " << it - q.front().begin() << endl;
                    it - q.front().begin();
                    _queue.addToQueue(q.front());
                }
            }
            q.pop();
        }
        cv.notify_one();
    }

public:
    LimitedQueue _queue;
    mutex tMut;
    std::condition_variable tCV;
    vector<char> generated;
    void Send(mutex &mu, queue<vector<char>> &q, condition_variable &cv)
    {
        lock_guard<mutex> lg(mu);
        cv.notify_one();
    }
    void Receive(mutex &mu, queue<vector<char>> &q, condition_variable &cv)
    {
        _Receive(mu, q, cv);
    }

    void print_array(vector<char> array) { _print_array(array); }
};

class ModuleThree : public IModule
{
private:
    void _print_array(vector<char> array)
    {
        for (int i = 0; i < array.size(); i++)
        {
            cout << array[i] << ',';
        }
        cout << endl;
    }

    void _Receive(mutex &mu, queue<vector<char>> &q, condition_variable &cv)
    {
        unique_lock<mutex> ul(mu);
        // cout << "modulo3_thread Receive" << endl;
        time_t t;

        cv.wait(ul, [&] { return (q.empty()) ? false : true; });

        if (q.empty())
        {
            cout << "No matches found" << endl;
        }
        else
        {
            cout << "Matches: " << endl;
        }
        while (!q.empty())
        {
            if (!q.front().empty())
            {
                t = time(NULL);
                generated = q.front();
                cout << endl;
                cout << date_to_str(t) << ":  ";
                print_array(q.front());
                q.pop();
            }
        }

        cv.notify_one();
    }

public:
    LimitedQueue _queue;
    mutex mut;
    std::condition_variable cval;
    vector<char> generated;
    void Send(mutex &mu, queue<vector<char>> &q, condition_variable &cv)
    {
        lock_guard<mutex> lg(mu);
        cv.notify_one();
    }
    void Receive(mutex &mu, queue<vector<char>> &q, condition_variable &cv)
    {
        _Receive(mu, q, cv);
    }

    void print_array(vector<char> array) { _print_array(array); }
};

std::string date_to_str(time_t t)
{
    char outstr[100];
    struct tm *tmp;
    const char *fmt = "%a, %d %b %y %T %z";
    tmp = gmtime(&t);

    strftime(outstr, sizeof(outstr), fmt, tmp);

    return string(outstr);
}
void th_modulo1(IModule &m, queue<vector<char>> &q, mutex &mu, condition_variable &cv)
{
    m.Send(mu, q, cv);
}
void th_modulo2(IModule &m, queue<vector<char>> &q, mutex &mu, condition_variable &cv)
{
    m.Receive(mu, q, cv);
}

void th_modulo3(IModule &m, queue<vector<char>> &q, mutex &mu, condition_variable &cv)
{
    m.Receive(mu, q, cv);
}
int main(int argc, char *argv[])
{
    cout << "Iniciando" << endl;

    ModuleOne m1;
    ModuleTwo m2;
    ModuleThree m3;
    queue<vector<char>> random_queue;

    std::thread modulo1(&th_modulo1, ref(m1), ref(random_queue), ref(m1.tMut), ref(m1.tCV));
    std::thread modulo2(&th_modulo2, ref(m2), ref(random_queue), ref(m1.tMut), ref(m1.tCV));
    std::thread modulo3(&th_modulo3, ref(m3), ref(m2._queue.q), ref(m1.tMut), ref(m1.tCV));

    modulo1.join();
    modulo2.join();
    modulo3.join();

    return EXIT_SUCCESS;
}
