double poly_opt(double a[], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0.0;
    double result2 = 0.0;
    double result3 = 0.0;
    
    double xpwr = x;
    double x2 = x * x;      // x²
    double x3 = x2 * x;     // x³
    double x4 = x2 * x2;    // x⁴
    double x5 = x4 * x;     // x⁵
    double x6 = x3 * x3;    // x⁶
    double x7 = x6 * x;     // x⁷
    double x8 = x4 * x4;    // x⁸
    
    // Process 8 terms per iteration
    for (i = 1; i + 7 <= degree; i += 8)
    {
        result0 = result0 + xpwr * (a[i] + a[i+3] * x3);
        result1 = result1 + xpwr * (a[i+1] * x + a[i+4] * x4);
        result2 = result2 + xpwr * (a[i+2] * x2 + a[i+5] * x5);
        result3 = result3 + xpwr * (a[i+6] * x6 + a[i+7] * x7);

        xpwr = xpwr * x8;
    }
    
    // Handle remaining terms (distribute among accumulators)
    for (; i <= degree; ++i)
    {
        switch((i - 1) % 4)
        {
            case 0: result0 += a[i] * xpwr; break;
            case 1: result1 += a[i] * xpwr; break;
            case 2: result2 += a[i] * xpwr; break;
            case 3: result3 += a[i] * xpwr; break;
        }
        xpwr = xpwr * x;
    }
    
    return result0 + result1 + result2 + result3;
}