
#include <iostream>
using namespace std;

double expo(int base, int exp)
{
    if (exp == 0)
        return 1.0;

    if (exp > 0)
        return base * expo(base, exp - 1);

    return (1.0 / base) * expo(base, exp + 1);
}

class LL
{
public:
    int bit;
    int pos;
    LL *next;

    LL(int value, int position)
    {
        bit = value;
        pos = position;
        next = nullptr;
    }
};

// Recursively delete the linked list
void DELETE(LL *root)
{
    if (root == nullptr)
        return;

    DELETE(root->next);
    delete root;
}

class toDecimal
{
private:
    int base;
    char data[100];
    double result;

    // Convert a character into its numerical digit value
    int getDigit(char ch)
    {
        if (ch >= '0' && ch <= '9')
            return ch - '0';

        if (ch >= 'A' && ch <= 'F')
            return ch - 'A' + 10;

        if (ch >= 'a' && ch <= 'f')
            return ch - 'a' + 10;

        return -1;
    }

    // Validate input and construct the linked list
    bool buildList(LL *&root, int &decimalPos)
    {
        LL *temp = nullptr;
        int counter = 0;
        bool decimalFound = false;
        bool hasDigit = false;

        root = nullptr;
        decimalPos = 0;

        for (int i = 0; data[i] != '\0'; i++)
        {
            if (data[i] == '.')
            {
                if (decimalFound || !hasDigit)
                    return false;

                decimalFound = true;
                decimalPos = counter;
                continue;
            }

            int digit = getDigit(data[i]);

            if (digit < 0 || digit >= base)
                return false;

            counter++;
            hasDigit = true;

            LL *newNode = new LL(digit, counter);

            if (root == nullptr)
                root = newNode;
            else
                temp->next = newNode;

            temp = newNode;
        }

        if (!hasDigit)
            return false;

        // If no decimal point exists, all digits are integer digits.
        if (!decimalFound)
            decimalPos = counter;

        return true;
    }

public:
    toDecimal()
    {
        result = 0.0;

        cout << "Enter the Base of Number System: ";
        cin >> base;

        cout << "Enter the Data to be converted: ";
        cin >> data;

        if (base < 2 || base > 16)
        {
            cout << "Invalid base. Supported range: 2 to 16.\n";
            return;
        }

        LL *root = nullptr;
        int decimalPos = 0;

        if (!buildList(root, decimalPos))
        {
            cout << "Invalid number representation!\n";
            DELETE(root);
            return;
        }

        LL *temp = root;

        while (temp != nullptr)
        {
            int exponent = decimalPos - temp->pos;

            result += temp->bit * expo(base, exponent);

            temp = temp->next;
        }

        DELETE(root);
    }

    double Result() const
    {
        return result;
    }
};

int main()
{
    toDecimal converter;

    cout << "Decimal Result: " << converter.Result() << '\n';

    return 0;
}
