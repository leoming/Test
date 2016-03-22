#ifndef PROGRESS_WRAPPER_H_
#define PROGRESS_WRAPPER_H_

/* This file defines a class to wrap progressbars */

class CProgress
{
public:
    virtual void setTotalSteps(int total) = 0;
    virtual void setProgress(int progress) = 0;
    virtual int progress() const = 0;
    virtual int totalSteps() const = 0;
    virtual void nextStep() = 0;
    virtual ~CProgress(){}
};

#endif /* ! PROGRESS_WRAPPER_H_ */
