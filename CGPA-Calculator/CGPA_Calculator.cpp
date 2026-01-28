#include<iostream>
#include<vector>
using namespace std;

class ICourse{
public:
    virtual double GetGradePoints() = 0;
    virtual int GetCredits() = 0;
    virtual ~ICourse() {} 
};

class Course : public ICourse{
private:
    double gradepoint;
    int credits;
public:
    Course(double gradepoint, int credits){
        this->gradepoint = gradepoint;
        this->credits = credits;
    }

    double GetGradePoints() override {
        return gradepoint;
    }

    int GetCredits() override {
        return credits;
    }

};


class ICalculator{
public:
    virtual double CalculateCGPA(vector<ICourse*> &courses) = 0;
    virtual ~ICalculator() {}
};

class CGPACalculator : public ICalculator{
public:
    double CalculateCGPA(vector<ICourse*> &courses) override {
        double totalgradepoints = 0;
        int totalcredits = 0;

        for(auto& course : courses){
            totalgradepoints += course->GetGradePoints() * course->GetCredits();
            totalcredits += course->GetCredits(); 
        }

        return (totalcredits == 0) ? 0.0 : totalgradepoints/totalcredits;
    }
};

class InputHandler{
public:
    static vector<ICourse*> Getcourses(){
        int n;
        cout << "Enter number of courses : ";
        cin >> n;
        vector<ICourse*> courses;

        for(int i=0; i<n; i++){
            double grade = 0;
            int credit = 0;
            cout << "Enter the grade point for the course " << i+1 << " : ";
            cin >> grade;
            cout << "Enter the credit hours for the course " << i+1 << " : ";
            cin >> credit;
            
            courses.push_back(new Course(grade, credit));
        }
        return courses;
    }
};


class DisplayService{
public:
    static void showresult(double cgpa){
        cout << "\nFinal CGPA is : " << cgpa << endl;
    }
};


int main(){
    vector<ICourse*> courses = InputHandler ::  Getcourses();

    ICalculator* calculator = new CGPACalculator();

    double cgpa = calculator->CalculateCGPA(courses);

    DisplayService :: showresult(cgpa);

    for(auto course : courses){
        delete course;
    }
    delete calculator;

    return 0;
}