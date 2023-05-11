#include "UnitTest.hpp"


void UnitTest::check_board_state(const std::unique_ptr<Board>& board, const uint64_t& initial_board_state) {

    ASSERT_EQ(board->get_state(), initial_board_state);

}


void UnitTest::initialize_default_board() {

    std::unique_ptr<Vehicle> player_vehicle {
        std::make_unique<PlayerVehicle>(0b0000'0000'0000'0000'0000'0000'0110'0000'0000'0000'0000'0000'0000'0000'0000'0000)
    };
    std::unique_ptr<Vehicle> truck_o {
        std::make_unique<VerticalVehicle>(0b0000'0000'0001'0000'0001'0000'0001'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'o')
    };
    std::unique_ptr<Vehicle> car_a {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0110'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'a')
    };
    std::unique_ptr<Vehicle> truck_p {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0111'0000'0000'0000'0000'0000'0000'0000, 'p')
    };
    std::unique_ptr<Vehicle> truck_q {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0010'0000'0010'0000'0010'0000'0000, 'q')
    };

    using vehicle_list = std::forward_list<std::unique_ptr<Vehicle>>;
    game_board = std::make_unique<Board>(
        make<vehicle_list>(
            std::move(player_vehicle), std::move(car_a),
            std::move(truck_o), std::move(truck_p), std::move(truck_q) ) );

    uint64_t initial_board_state { 0b1111'1111'1001'0111'1001'0001'1111'0000'1111'0011'1000'0011'1000'0011'1111'1111 };

    check_board_state(game_board, initial_board_state);

}


void UnitTest::initialize_no_solution_board() {


    std::unique_ptr<Vehicle> player_vehicle {
        std::make_unique<PlayerVehicle>(0b0000'0000'0000'0000'0000'0000'0011'0000'0000'0000'0000'0000'0000'0000'0000'0000)
    };
    std::unique_ptr<Vehicle> truck_o {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0010'0000'0010'0000'0010'0000'0000'0000'0000'0000'0000'0000'0000, 'o')
    };
    std::unique_ptr<Vehicle> truck_p {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0010'0000'0010'0000'0010'0000'0000, 'p')
    };
    std::unique_ptr<Vehicle> car_q {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0110'0000'0000'0000, 'q')
    };

    using vehicle_list = std::forward_list<std::unique_ptr<Vehicle>>;
    game_board = std::make_unique<Board>(
        make<vehicle_list>( std::move(player_vehicle), std::move(truck_o), std::move(truck_p), std::move(car_q) ) );

}


void UnitTest::initialize_sample_board1() {

    std::unique_ptr<Vehicle> truck_o {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0001'1100'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'o')
    };
    std::unique_ptr<Vehicle> truck_p {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0111'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'p')
    };
    std::unique_ptr<Vehicle> truck_q {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0000'0100'0000'0100'0000'0100'0000'0000'0000'0000'0000'0000, 'q')
    };
    std::unique_ptr<Vehicle> player_vehicle {
        std::make_unique<PlayerVehicle>(0b0000'0000'0000'0000'0000'0000'0110'0000'0000'0000'0000'0000'0000'0000'0000'0000)
    };
    std::unique_ptr<Vehicle> truck_r {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0111'0000'0000'0000'0000'0000'0000'0000, 'r')
    };
    std::unique_ptr<Vehicle> car_a {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0010'0000'0010'0000'0000'0000'0000'0000'0000, 'a')
    };
    std::unique_ptr<Vehicle> car_b {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0100'0000'0100'0000'0000'0000, 'b')
    };
    std::unique_ptr<Vehicle> car_c {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0001'0000'0001'0000'0000'0000, 'c')
    };
    std::unique_ptr<Vehicle> car_d {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0110'0000'0000'0000'0000, 'd')
    };
    std::unique_ptr<Vehicle> car_e {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0110'0000'0000, 'e')
    };

    using vehicle_list = std::forward_list<std::unique_ptr<Vehicle>>;
    game_board = std::make_unique<Board>( make<vehicle_list>( std::move(truck_o), std::move(truck_p), std::move(truck_q),
        std::move(player_vehicle), std::move(truck_r), std::move(car_a), std::move(car_b), std::move(car_c),
        std::move(car_d), std::move(car_e) ) );

    uint64_t initial_board_state { 0b1111'1111'1001'1101'1111'0101'1110'0110'1111'0111'1101'0111'1101'0111'1111'1111 };

    check_board_state(game_board, initial_board_state);

}


void UnitTest::initialize_sample_board3() {

    std::unique_ptr<Vehicle> player_vehicle {
        std::make_unique<PlayerVehicle>(0b0000'0000'0000'0000'0000'0000'0000'1100'0000'0000'0000'0000'0000'0000'0000'0000)
    };
    std::unique_ptr<Vehicle> car_a {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0110'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'a')
    };
    std::unique_ptr<Vehicle> car_b {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0001'1000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'b')
    };
    std::unique_ptr<Vehicle> car_c {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0100'0000'0100'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'c')
    };
    std::unique_ptr<Vehicle> car_d {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0100'0000'0100'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'd')
    };
    std::unique_ptr<Vehicle> car_e {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0001'1000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'e')
    };
    std::unique_ptr<Vehicle> car_f {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0000'0000'0010'0000'0010'0000'0000'0000'0000'0000'0000'0000, 'f')
    };
    std::unique_ptr<Vehicle> car_h {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0110'0000'0000'0000, 'h')
    };
    std::unique_ptr<Vehicle> truck_o {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0010'0000'0010'0000'0010'0000'0000'0000'0000'0000'0000'0000'0000, 'o')
    };
    std::unique_ptr<Vehicle> truck_p {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0000'0000'0001'0000'0001'0000'0001'0000'0000'0000'0000'0000, 'p')
    };
    std::unique_ptr<Vehicle> truck_q {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0000'1110'0000'0000'0000'0000'0000'0000, 'q')
    };

    using vehicle_list = std::forward_list<std::unique_ptr<Vehicle>>;
    game_board = std::make_unique<Board>(
        make<vehicle_list>(
            std::move(player_vehicle), std::move(car_a), std::move(car_b),
            std::move(car_c), std::move(car_d), std::move(car_e), std::move(car_f), std::move(car_h),
            std::move(truck_o), std::move(truck_p), std::move(truck_q) ) );

    uint64_t game_state_bit_board { 0b1111'1111'1111'1111'1101'1111'1111'1110'1011'1111'1001'0001'1110'0001'1111'1111 };

    check_board_state(game_board, game_state_bit_board);

}


void UnitTest::initialize_solution_board() {

    std::unique_ptr<Vehicle> player_vehicle {
        std::make_unique<PlayerVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0110'0000'0000'0000'0000'0000'0000'0000'0000)
    };

    using vehicle_list = std::forward_list<std::unique_ptr<Vehicle>>;
    game_board = std::make_unique<Board>(
        make<vehicle_list>( std::move(player_vehicle) ) );

}
