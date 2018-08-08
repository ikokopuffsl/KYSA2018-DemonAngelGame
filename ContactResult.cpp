#include "ContactResult.h"

ContactResult::ContactResult(string type, int count) {
    contactResultType = type;
    contactResultVaccineCount = count;
}

string ContactResult::GetType() {
    return contactResultType;
}

int ContactResult::GetCount() {
    return contactResultVaccineCount;
}