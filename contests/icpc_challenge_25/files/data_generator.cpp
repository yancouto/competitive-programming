#include <bits/stdc++.h>
#include "testlib.h"

// Deterministic random distribution functions ---

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

template<typename T>
double uniform_double_from_gen(T& gen) {
    return static_cast<double>(gen()) / (static_cast<double>(T::max()) + 1.0);
}

template<typename T>
double generate_normal(T& gen, double mu, double sigma) {
    static volatile double z1;
    static bool has_z1 = false;
    
    if (has_z1) {
        has_z1 = false;
        volatile double res_sigma = z1 * sigma;
        volatile double res_mu = res_sigma + mu;
        return res_mu;
    }

    volatile double u1, u2;
    do {
        u1 = uniform_double_from_gen(gen);
        u2 = uniform_double_from_gen(gen);
    } while (u1 <= 1e-9);

    volatile double term1 = -2.0;
    volatile double log_u1 = log(u1);
    volatile double term2 = term1 * log_u1;
    volatile double sqrt_term = sqrt(term2);

    volatile double term3 = 2.0;
    volatile double term4 = M_PI;
    volatile double term5 = term3 * term4;
    volatile double term6 = term5 * u2;
    
    volatile double cos_term = cos(term6);
    volatile double sin_term = sin(term6);

    volatile double z0 = sqrt_term * cos_term;
    z1 = sqrt_term * sin_term;
    
    has_z1 = true;

    volatile double res_sigma = z0 * sigma;
    volatile double res_mu = res_sigma + mu;
    return res_mu;
}

template<typename T>
double generate_gamma(T& gen, double alpha) {
    if (alpha < 1.0) {
        volatile double u = uniform_double_from_gen(gen);
        volatile double new_alpha = 1.0 + alpha;
        volatile double recursive_gamma = generate_gamma(gen, new_alpha);
        volatile double u_pow = pow(u, 1.0 / alpha);
        return recursive_gamma * u_pow;
    }

    volatile double d = alpha - 1.0 / 3.0;
    volatile double c = 1.0 / sqrt(9.0 * d);
    volatile double x, v, u;

    while (true) {
        do {
            x = generate_normal(gen, 0.0, 1.0);
            volatile double term1 = c * x;
            v = 1.0 + term1;
        } while (v <= 0);
        
        volatile double v_cubed = v * v * v;
        u = uniform_double_from_gen(gen);

        volatile double x_sq = x * x;
        volatile double x_pow4 = x_sq * x_sq;
        volatile double check1_term = 0.0331 * x_pow4;
        if (u < 1.0 - check1_term) {
            return d * v_cubed;
        }

        volatile double log_u = log(u);
        volatile double term2 = 0.5 * x_sq;
        volatile double log_v = log(v);
        volatile double term3 = 1.0 - v_cubed + log_v;
        volatile double term4 = d * term3;
        if (log_u < term2 + term4) {
            return d * v_cubed;
        }
    }
}

const std::vector<std::pair<int, int>> universal_sizes = {
	{6, 6}, {9, 9}, {12, 12},
	{6, 12}, {12, 6},
	{6, 18}, {18, 6},
	{4, 12}, {12, 4},
	{6, 4}, {4, 6},
	{9, 6}, {6, 9},
	{9, 12}, {12, 9},
	{14, 6}
};

const int NUM_UNIVERSAL_SIZES = (int)universal_sizes.size();
const int SIX_BY_SIX_INDEX = 0;
 
int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
 
	int G = opt<int>(1);
	int N_total = opt<int>(2);
	int K = opt<int>(3);
	std::string dist_type = opt<std::string>(4); // "rnd" or "beta"
	double dist_para1 = opt<double>(5); // mu for normal, alpha for beta
	double dist_para2 = opt<double>(6); // sigma for normal, beta for beta
 
	// This generator is used as a deterministic source of randomness for weights.
	std::mt19937 generator_for_weights( (unsigned int)rnd.next() );
 
	printf("%d %d\n", G, K);
 
	std::vector<int> group_photo_counts(G);
	if (G == 1) {
		group_photo_counts[0] = N_total;
	} else {
		std::vector<int> divider_positions = rnd.distinct(G - 1, 1, N_total - 1);
		std::sort(divider_positions.begin(), divider_positions.end());
 
		std::vector<int> final_dividers;
		final_dividers.push_back(0);
		for (int pos : divider_positions) {
			final_dividers.push_back(pos);
		}
		final_dividers.push_back(N_total);
 
		for (int i = 0; i < G; ++i) {
			group_photo_counts[i] = final_dividers[i + 1] - final_dividers[i];
		}
	}
 
	for (int i = 0; i < G; ++i) {
		int N_i = group_photo_counts[i];
		printf("%d\n", N_i);
 
		for (int j = 0; j < N_i; ++j) {
			int num_to_remove = rnd.next(0, std::min(NUM_UNIVERSAL_SIZES - 2, 3));
			int T_ij = NUM_UNIVERSAL_SIZES - num_to_remove;
			
			printf("%d", T_ij);
 
			std::vector<int> permuted_indices = rnd.perm(NUM_UNIVERSAL_SIZES);
 
			std::set<int> selected_indices_set;
			selected_indices_set.insert(SIX_BY_SIX_INDEX);
 
			int count_added = 1;
			for (int k = 0; k < NUM_UNIVERSAL_SIZES && count_added < T_ij; ++k) {
				int current_idx = permuted_indices[k];
				if (current_idx != SIX_BY_SIX_INDEX && selected_indices_set.find(current_idx) == selected_indices_set.end()) {
					selected_indices_set.insert(current_idx);
					count_added++;
				}
			}
			
			std::vector<int> final_selected_indices(selected_indices_set.begin(), selected_indices_set.end());
			std::sort(final_selected_indices.begin(), final_selected_indices.end());
 
			for (int idx : final_selected_indices) {
				int width = universal_sizes[idx].first;
				int height = universal_sizes[idx].second;

				double weight;
                do {
                    double raw_weight = 0.0;

                    if (dist_type == "beta") {
                        // Generate Beta(alpha, beta) from Gamma(alpha, 1) and Gamma(beta, 1).
                        double x_from_gamma = generate_gamma(generator_for_weights, dist_para1);
                        double y_from_gamma = generate_gamma(generator_for_weights, dist_para2);
                        if (x_from_gamma + y_from_gamma > 1e-9) { // Avoid division by zero.
                            raw_weight = x_from_gamma / (x_from_gamma + y_from_gamma) * 100.0;
                        }
                    } else { // Generate a raw value from the unbounded normal distribution.
                        raw_weight = generate_normal(generator_for_weights, dist_para1, dist_para2);
                    }
                    
                    weight = raw_weight;

                } while (weight < 0.0 || weight > 100.0); // Reject and retry if outside [0, 100].
				
				printf(" %d %d %.10f", width, height, weight);
			}
			printf("\n");
		}
	}
 
	return 0;
}