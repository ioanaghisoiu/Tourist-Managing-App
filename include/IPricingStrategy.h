#pragma once

class IPricingStrategy {
public:
    virtual ~IPricingStrategy() = default;
    virtual double calculatePrice(double basePrice) const = 0;
};

class StandardPricingStrategy : public IPricingStrategy {
public:
    double calculatePrice(double basePrice) const override {
        return basePrice;
    }
};

class DiscountPricingStrategy : public IPricingStrategy {
    double discountRate;
public:
    explicit DiscountPricingStrategy(double rate) : discountRate(rate) {}
    double calculatePrice(double basePrice) const override {
        return basePrice * (1.0 - discountRate);
    }
};

class FreePricingStrategy : public IPricingStrategy {
public:
    double calculatePrice(double /*basePrice*/) const override {
        return 0.0;
    }
};