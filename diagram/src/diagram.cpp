#include "diagram.h"

namespace timeD {
    Diagram::Diagram (const char *acds) { //TODO test 010101010
         int len = strlen(acds);

        sigNum = 0;
        length = 0;
        scale = 1;
        interval = new signal[10];

        if (!len)
            return;

        if (len > maxLen)
            throw std::invalid_argument("Too big input");

        char last = acds[0];

        int curstart = 0;

        for (int i = 1; i <= len; ++i) {
            if (i == len) {
                addSignal(last, curstart, i - curstart);
                length = len;
            }
            else if (acds[i] != last) {
                addSignal(last, curstart, i - curstart);
                curstart = i;
                last = acds[i];
                length = i;
            }
        }
    }

    Diagram::Diagram(const Diagram &reference): sigNum(reference.sigNum), length(reference.length), scale(reference.scale) {
        interval = new signal[scale * magnifier];
        for (int i = 0; i < sigNum; ++i) {
            copyInterval(reference, i, i);
        }
    }

    Diagram::Diagram (Diagram && reference): sigNum(reference.sigNum), length(reference.length), scale(reference.scale), interval(reference.interval) {
        reference.interval = nullptr;
    }

    Diagram & Diagram::addSignal(char symb, int start, int len) {
        if (start < length)
            throw std::invalid_argument("Incorrect start position");
        if (start + len > maxLen)
            throw std::invalid_argument("Diagram is too big");

        if (len <= 0)
            return *this;

        bool sigVal;

        if (symb == '0') {
            sigVal = 0;
        } else if (symb == '1') {
            sigVal = 1;
        } else if (symb == 'X') {
            length = start + len;
            return *this;
        } else {
            throw std::invalid_argument("Incorrect signal");
        }

        if (sigNum >= maxSig)
            throw std::invalid_argument("Count of signals is too big");

        if (sigNum > 0 && interval[sigNum-1].val == sigVal && interval[sigNum-1].start + interval[sigNum-1].length == start) {
            interval[sigNum-1].length += len;
        } else {
            if (sigNum >= magnifier * scale) {
                signal *old = interval;
                interval = new signal[magnifier * (++scale)];
                for (int i = 0; i < sigNum; ++i) {
                    copyInterval(old, i, i);
                }
                delete[] old;
            }

            interval[sigNum].val = sigVal;
            interval[sigNum].start = start;
            interval[sigNum].length = len;
            sigNum++;
        }

        length = start + len;

        return *this;
    }

    Diagram & Diagram::operator =(const Diagram &reference) {
        if (this != &reference) {
            length = reference.length;
            sigNum = reference.sigNum;
            scale = reference.scale;
            delete[] interval;
            interval = new signal[scale * magnifier];

            for (int i = 0; i < sigNum; ++i) {
                copyInterval(reference, i, i);
            }
        }
        return *this;
    }

    Diagram & Diagram::operator =(Diagram &&reference) {
        length = reference.length;
        sigNum = reference.sigNum;
        scale = reference.scale;
        delete[] interval;
        interval = reference.interval;
        reference.interval = nullptr;
        return *this;
    }

    Diagram & Diagram::operator += (const Diagram &conc) {
        if (length + conc.length > maxLen)
            throw std::invalid_argument("Invalid lengths");
        if (sigNum + conc.sigNum > maxSig)
            throw std::invalid_argument("Invalid count of signals");

        int ist = 0;
        if(interval[sigNum-1].val == conc.interval[0].val && conc.interval[0].start == 0) {
            interval[sigNum-1].length += conc.interval[0].length;
            ist = 1;
        }

        int newScale = (sigNum - ist + conc.sigNum) / magnifier;
        if ((sigNum + conc.sigNum) % magnifier > 0)
            ++newScale;

        if (newScale > scale) {
            signal *old = interval;
            interval = new signal[magnifier * newScale];
            for (int ia = 0; ia < sigNum; ++ia) {
                copyInterval(old, ia, ia);
            }
            delete[] old;
            scale = newScale;
        }

        for (int i = ist; i < conc.sigNum; ++i) {
            interval[sigNum + i - ist].val = conc.interval[i].val;
            interval[sigNum + i - ist].start = conc.interval[i].start + length;
            interval[sigNum + i - ist].length = conc.interval[i].length;
        }

        length += conc.length;
        sigNum += conc.sigNum - ist;

        return *this;
    }

    Diagram & Diagram::operator++() {
        *this += *this; // !!!
        return *this;
    }

    Diagram Diagram::operator++(int) {
        Diagram diag = *this;
        ++(*this);
        return diag;
    }

    Diagram operator + (const Diagram & ftestm, const Diagram & sterm) {
        Diagram diag = ftestm;
        diag += sterm;
        return diag;
    }

    int Diagram::copyDiagram(int count) {
        if (length * count > maxLen)
            return 1;
        if (sigNum * count > maxSig)
            return 1;

        int sigst = 0;
        int sigP = 0;

        if (interval[sigNum - 1].val == interval[0].val && interval[0].start == 0) {
            if (sigNum == 1) {
                length *= count;
                interval[0].length *= count;
                return 0;
            }

            interval[sigNum - 1].length += interval[0].length;
            sigst = interval[0].length;
            sigP = 1;
        }

        int newScale = (sigNum * count) / magnifier;
        if ((sigNum * count) % magnifier > 0)
            ++newScale;

        if (newScale > scale) {
            signal *old = interval;
            interval = new signal[magnifier * newScale];
            for (int ia = 0; ia < sigNum; ++ia) {
                copyInterval(old, ia, ia);
            }
            scale = newScale;
            delete[] old;
        }

        for (int sig = sigP; sig < sigNum; sig++) {
            for (int i = 1; i < count; i++) {
                interval[(sigNum - sigP)*i + sig].val = interval[sig].val;
                interval[(sigNum - sigP)*i + sig].start = interval[sig].start + length*i;
                interval[(sigNum - sigP)*i + sig].length = interval[sig].length;
            }
        }

        length *= count;

        if (sigP)
            sigNum = count * (sigNum - 1) + 1;
        else
            sigNum *= count;

        interval[sigNum - 1].length -= sigst;
        return 0;
    }

    int Diagram::cutDiag(int moment) { // don't forget about freeing mem
        int sig;

        for (sig = 0; sig < sigNum; ++sig) {
            if(interval[sig].start + interval[sig].length > moment) { //start of next signal
                if (interval[sig].start < moment) {
                    interval[sig].length = moment - interval[sig].start;
                    sigNum = sig + 1;
                    length = moment;
                }
                else { //cutting in X, nothing to change
                    sigNum = sig;
                    length = moment;
                }

                scale = (sig+1) / magnifier;
                if ((sig+1) % magnifier > 0 || !scale)
                    ++scale;
                return 0;
            }
        }

        if (moment >= length)
            return 1;
        else {
            length = moment;
            return 0;
        }
    }

    Diagram &Diagram::replace(int moment, const Diagram &add) {
        if (&add == this)
            return *this;

        int oldScale = scale;

        int cutLeft = (*this).Diagram::cutDiag(moment);
        if (cutLeft == 1)
            throw std::invalid_argument("Incorrect position");

        int sigAdd;
        for (sigAdd = 0; sigAdd < add.sigNum; ++sigAdd) {
            if (add.interval[sigAdd].start + add.interval[sigAdd].length > moment) {
                if (add.interval[sigAdd].start <= moment) {
                    if (interval[sigNum-1].val == add.interval[sigAdd].val) {
                        interval[sigNum-1].length += add.interval[sigAdd].start + add.interval[sigAdd].length - moment;
                        sigNum--;
                    }
                    else {
                        if (sigNum >= magnifier * scale) {
                            signal *old = interval;
                            interval = new signal[magnifier * (++scale)];
                            for (int i = 0; i < sigNum; ++i) {
                                copyInterval(old, i, i);
                            }
                            delete[] old;
                        }

                        interval[sigNum].val = add.interval[sigAdd].val;
                        interval[sigNum].start = moment;
                        interval[sigNum].length = add.interval[sigAdd].start + add.interval[sigAdd].length - moment;
                    }
                }
                else {
                    if (sigNum >= magnifier * scale) {
                        signal *old = interval;
                        interval = new signal[magnifier * (++scale)];
                        for (int i = 0; i < sigNum; ++i) {
                            copyInterval(old, i, i);
                        }
                        delete[] old;
                    }

                    copyInterval(add, sigNum, sigAdd);
                }

                length = interval[sigNum].start + interval[sigNum].length;
                sigNum++;

            }
        }

        if (scale < oldScale) {
            signal *old = interval;
            interval = new signal[magnifier * scale];
            for (int i = 0; i < sigNum; ++i) {
                interval[i].start = old[i].start;
                interval[i].length = old[i].length;
                interval[i].val = old[i].val;
            }
            delete[] old;
        }

        return *this;
    }

    int Diagram::shift(int times) {
        for (int sig = 0; sig < sigNum; ++sig) {
            interval[sig].start += times;
        }

        length += times;

        return 0;
    }

    Diagram & Diagram::operator << (int times) {
        if (times < 0)
            throw std::invalid_argument("Negative shift");
        shift(-times);

        if (interval[0].start < 0) {
            for (int sig = 0; sig < sigNum; ++sig) {
                if (interval[sig].start + interval[sig].length > 0) {
                    if (interval[sig].start < 0) {
                        interval[sig].length += interval[sig].start;
                        interval[sig].start = 0;
                    }

                    for (int i = sig; i < sigNum; ++i) {
                        copyInterval(*this, i-sig, i);
                    }

                    sigNum -= sig;

                    prettyInterval();

                    return *this;
                }
            }

            length = 0;
            sigNum = 0;
            scale = 1;
            delete[] interval;
            interval = new signal[magnifier];
        } else if(sigNum == 0 && length < 0) {
            length = 0;
        }

        return *this;
    }

    Diagram & Diagram::operator >> (int times) {
        if (times < 0)
            throw std::invalid_argument("Negative shift");
        shift(times);

        if (length > maxLen) {
            for (int sig = sigNum-1; sig >= 0; --sig) {
                if (interval[sig].start < maxLen) {
                    sigNum = sig + 1;
                    length = maxLen;
                    if (interval[sig].start + interval[sig].length > maxLen) {
                        interval[sig].length = maxLen - interval[sig].start;
                    }

                    prettyInterval();

                    return *this;
                }
            }

            length = maxLen;
            sigNum = 0;
            scale = 1;
            delete[] interval;
            interval = new signal[magnifier];

        }

        return *this;
    }

    int Diagram::operator() (const int a, const int b, Diagram &diag) const { // [ )
        if (a >= length || b > length || a >= b)
            throw std::invalid_argument("Incorrect interval");

        int start = sigNum-1;
        int end = sigNum-1;

        for (int sig = 0; sig < sigNum; ++sig) {
            if (interval[sig].start + interval[sig].length > a) {
                start = sig;
                break;
            }
        }

        for (int sig = start; sig < sigNum; ++sig) {
            if (interval[sig].start + interval[sig].length >= b) {
                if (interval[sig].start >= b)
                    end = sig-1;
                else
                    end = sig;
                break;
            }
        }


        if (start > end) {
            diag.sigNum = 0;
            diag.length = b - a;
            return 0;
        }
        else if (start == end && start == sigNum-1 && a > interval[sigNum - 1].start) {
            diag.sigNum = 0;
            diag.length = b - a;
            return 0;
        }
        else {
            int first_start = 0;
            int first_length = interval[start]. start + interval[start].length - a;
            if (first_length > interval[start].length) {
                first_start = first_length - interval[start].length;
                first_length = interval[start].length;
            }

            int full_len = b - a;
            int end_length = b - interval[end].start;

            if (end_length > interval[end].length)
                end_length = interval[end].length;

            diag.sigNum = end - start + 1;
            diag.length = b - a;
            diag.prettyInterval();

            for (int i = 0; i < sigNum; ++i) {
                diag.interval[i].val = interval[i + start].val;
                diag.interval[i].start = interval[i + start].start - a;
                diag.interval[i].length = interval[i + start].length;
            }

            diag.interval[0].start = first_start;
            diag.interval[0].length = first_length;
            diag.interval[diag.sigNum - 1].length = end_length;

            return 0;

        }

    }

    void Diagram::copyInterval(const Diagram & recipient, int leftPos, int rightPos) {
        interval[leftPos].val = recipient.interval[rightPos].val;
        interval[leftPos].start = recipient.interval[rightPos].start;
        interval[leftPos].length = recipient.interval[rightPos].length;
    }

    void Diagram::copyInterval(const timeD::signal * old, int leftPos, int rightPos) {
        interval[leftPos].start = old[rightPos].start;
        interval[leftPos].length = old[rightPos].length;
        interval[leftPos].val = old[rightPos].val;
    }

    int Diagram::refScale() {
        int newScale = sigNum / magnifier;
        if (sigNum % magnifier > 0)
            ++newScale;
        if (!newScale)
            return 1;
        return newScale;
    }

    void Diagram::prettyInterval() {
        if (refScale() != scale) {
            signal *old = interval;
            interval = new signal[refScale() * magnifier];
            for (int i = 0; i < sigNum; ++i) {
                copyInterval(old, i, i);
            }
            delete[] old;
            scale = refScale();
        }
    }

    std::ostream & Diagram::printDiagram(std::ostream& stream) const {
        if (length > 500)
            return stream;

        int pos = 0;
        int signalEl = 0;
        stream << "Time\t0\t1" << std::endl;
        while (pos < length) {
            if (signalEl >= sigNum || pos < interval[signalEl].start) {
                stream << pos << std::endl;
                pos++;
            } else {
                for(; pos < interval[signalEl].start + interval[signalEl].length; pos++) {
                    if (interval[signalEl].val == 1)
                        stream << pos << "\t\t|" << std::endl;
                    else {
                        stream << pos << "\t|\t" << std::endl;
                    }
                }
                signalEl++;
            }

        }
        return stream;
    }

    std::ostream & Diagram::printSignals(std::ostream& stream) const {
        stream << "length: " << length << std::endl;
        stream << "Scale: " << scale << std::endl;
        stream << "\tSignal\tstart\tlength" << std::endl;
        for (int i = 0; i < sigNum; i++) {
            stream << i << ".\t" << interval[i].val << "\t" << interval[i].start << "\t" << interval[i].length << std::endl;
        }

        return stream;
    }

    std::ostream & operator << (std::ostream &stream, const Diagram & diag) {
        diag.printDiagram(stream);
        diag.printSignals(stream);

        return stream;
    }

    std::istream & operator >> (std::istream &stream, Diagram & diag) {
        char getst[diag.maxLen];

        stream.getline(getst, diag.maxLen + 1);

        if (!stream.good()) {
            return stream;
        }

        try {
            timeD::Diagram diagr(getst);
            diag = diagr;
        } catch (std::exception &ex){
            stream.setstate(std::ios_base::failbit);
        }

        return stream;
    }
}