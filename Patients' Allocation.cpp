#include <iostream>
#include <vector>
#include <string>
using namespace std;

// PatientInfo class, it will contain information of patient like, name, age and criticalness assigned


class PatientInfo
{
    string name;
    int age;
    int criticalness; // it is the property that will be assigned to patient according to his diagnosis, (0 to 10)


public:


    // this constructor will initialize differnt properties for patient
    PatientInfo(string name, int age, int criticalness)
    {
        this->name = name;
        this->age = age;
        this->criticalness = criticalness;
    }

    // function to get criticalness of a patient
    int getCriticalness()
    {
        return this->criticalness;
    }

    // to print information
    void printPatientInfo()
    {
        cout << "Name: " << this->name << " Age: " << this->age << " Criticalness: " << this->criticalness << endl;
        cout << endl;
    }
};

class DoctorQueue
{
    // Data members
    vector<PatientInfo *> *patientArray; // this will hold patients info, and act as underlying DS for queue
    int currPatients;                    // total number of patients currently present in queue

    // to get left child of a node
    int left(int i)
    {
        return 2 * i + 1;
    }

    // to get right child of a node
    int right(int i)
    {
        return 2 * i + 2;
    }

    // to get a parent of a node
    int parent(int i)
    {
        return (i - 1) / 2;
    }

    // this function adjusts the heap, such that only root node passed may be violating the property of heap
    void maxHeapify(int i)
    {
        int rightChildIndex = right(i);
        int leftChildIndex = left(i);
        int bigger = i;
        if (leftChildIndex < currPatients && patientArray->at(leftChildIndex)->getCriticalness() > patientArray->at(i)->getCriticalness())
        {
            bigger = leftChildIndex;
        }
        if (rightChildIndex < currPatients && patientArray->at(rightChildIndex)->getCriticalness() > patientArray->at(bigger)->getCriticalness())
        {
            bigger = rightChildIndex;
        }
        if (bigger != i)
        {
            swap(patientArray->at(i), patientArray->at(bigger));
            maxHeapify(bigger);
        }
    }

public:
    // constructor to initialize the queue
    DoctorQueue()
    {
        this->currPatients = 0;
        this->patientArray = new vector<PatientInfo *>();
    }

    // get information of new patient from operator and push this new patient in queue
    void insertNewPatient()
    {
        // taking info from patient
        string name;
        int age;
        int criticalness;
        cout << "Enter name of patient: ";
        cin >> name;
        cout << "Enter age of patient: ";
        cin >> age;
        cout << "Enter criticalness diagnossed or assigned by doctor: ";
        cin >> criticalness;

        PatientInfo *newPatient = new PatientInfo(name, age, criticalness);
        currPatients++;

        patientArray->push_back(newPatient);
        int size = patientArray->size();
        for (int i = size - 1; i != 0 && patientArray->at(parent(i))->getCriticalness() < patientArray->at(i)->getCriticalness();)
        {
            swap(patientArray->at(i), patientArray->at(parent(i)));
            i = parent(i);
        }
    }

    // it will return most critical patient
    PatientInfo *top()
    {
        if (currPatients == 0)
            return NULL;

        return patientArray->at(0);
    }

    // it will return and remove most critical patient, as doctor will call
    PatientInfo *callMostCritical()
    {
        if (currPatients == 0)
            return NULL;

        if (currPatients == 1)
        {
            PatientInfo *toReturn = patientArray->at(0);
            patientArray->pop_back();
            currPatients--;
            return toReturn;
        }

        PatientInfo *toReturn = patientArray->at(0);
        swap(patientArray->at(0), patientArray->at(currPatients - 1));
        patientArray->pop_back();
        currPatients--;
        maxHeapify(0);
        return toReturn;
    }

    // if we want to see info all the patients, this function can be used
    void print()
    {
        for (int i = 0; i < patientArray->size(); i++)
            patientArray->at(i)->printPatientInfo();
    }

    // this will return total patients currently present in the queue
    int totalPatients()
    {
        return currPatients;
    }

    // this will tell whether the queue is empty or not
    bool isEmpty()
    {
        return currPatients == 0;
    }
};

int main()
{
    int numPatients;
    cout << "Enter Number of Patients : ";
    cin >> numPatients;
    cout << "\nEnter Information of " << numPatients << " patients\n\n";
    DoctorQueue doctorQueue;
    for (int i = 0; i < numPatients; i++)
    {
        doctorQueue.insertNewPatient();
        cout << endl;
    }
    cout << "\nOrder in which doctor is going to see the patients\n\n";
    for (int i = 0; i < numPatients; i++)
    {
        PatientInfo *info = doctorQueue.callMostCritical();
        if (info == NULL)
        {
            cout << "Queue is empty" << endl;
        }
        info->printPatientInfo();
        cout << "\n";
    }
    return 0;
}