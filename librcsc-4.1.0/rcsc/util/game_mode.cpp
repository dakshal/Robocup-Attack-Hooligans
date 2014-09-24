// -*-c++-*-

/*!
  \file game_mode.cpp
  \brief playmode wrapper Source File
*/

/*
 *Copyright:

 Copyright (C) Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <rcsc/game_mode.h>

#include <iostream>
#include <cstdlib>
#include <cstring>

namespace {

typedef std::map< std::string, rcsc::GameMode::Pair > PlayModeMap;

/*!
  \class MapHolder
  \brief interface to the playmode map. singleton map holder
*/
class MapHolder {
private:
    //! key: playmode string, value: playmode type
    PlayModeMap M_playmode_map;

    /*!
      \brief private access for singleton. create playmode map.
    */
    MapHolder();

public:

    ~MapHolder()
      {
          //std::cerr << "delete MapHolder map" << std::endl;
          M_playmode_map.clear();
          //std::cerr << "delete MapHolder done map.clear" << std::endl;
      }

    static
    const
    MapHolder & instance()
      {
          static MapHolder s_instance;
          return s_instance;
      }

    /*!
      \brief singleton interface. get playmode map
      \return const reference to the playmode map
    */
    const
    PlayModeMap & get() const
      {
          return M_playmode_map;
      }

};

/*-------------------------------------------------------------------*/
/*!

*/
MapHolder::MapHolder()
{
    using namespace rcsc;

    M_playmode_map["before_kick_off"] = std::make_pair( GameMode::BeforeKickOff, NEUTRAL );
    M_playmode_map["time_over"] = std::make_pair( GameMode::TimeOver, NEUTRAL );
    M_playmode_map["play_on"] = std::make_pair( GameMode::PlayOn, NEUTRAL );
    M_playmode_map["kick_off_l"] = std::make_pair( GameMode::KickOff_, LEFT );
    M_playmode_map["kick_off_r"] = std::make_pair( GameMode::KickOff_, RIGHT );
    M_playmode_map["kick_in_l"] = std::make_pair( GameMode::KickIn_, LEFT );
    M_playmode_map["kick_in_r"] = std::make_pair( GameMode::KickIn_, RIGHT );
    M_playmode_map["free_kick_l"] = std::make_pair( GameMode::FreeKick_, LEFT );
    M_playmode_map["free_kick_r"] = std::make_pair( GameMode::FreeKick_, RIGHT );
    M_playmode_map["corner_kick_l"] = std::make_pair( GameMode::CornerKick_, LEFT );
    M_playmode_map["corner_kick_r"] = std::make_pair( GameMode::CornerKick_, RIGHT );
    M_playmode_map["goal_kick_l"] = std::make_pair( GameMode::GoalKick_, LEFT );
    M_playmode_map["goal_kick_r"] = std::make_pair( GameMode::GoalKick_, RIGHT );
    // "goal_l"
    // "goal_r"
    M_playmode_map["drop_ball"] = std::make_pair( GameMode::PlayOn, NEUTRAL );
    M_playmode_map["offside_l"] = std::make_pair( GameMode::OffSide_, LEFT );
    M_playmode_map["offside_r"] = std::make_pair( GameMode::OffSide_, RIGHT );
    M_playmode_map["penalty_kick_l"]  = std::make_pair( GameMode::PenaltyKick_, LEFT );
    M_playmode_map["penalty_kick_r"]  = std::make_pair( GameMode::PenaltyKick_, RIGHT );
    M_playmode_map["first_half_over"] = std::make_pair( GameMode::FirstHalfOver, NEUTRAL );
    M_playmode_map["pause"]           = std::make_pair( GameMode::Pause, NEUTRAL );
    M_playmode_map["human_judge"]     = std::make_pair( GameMode::Human, NEUTRAL );
    M_playmode_map["foul_charge_l"]   = std::make_pair( GameMode::FoulCharge_, LEFT );
    M_playmode_map["foul_charge_r"]   = std::make_pair( GameMode::FoulCharge_, RIGHT );
    M_playmode_map["foul_push_l"]     = std::make_pair( GameMode::FoulPush_,    LEFT );
    M_playmode_map["foul_push_r"]     = std::make_pair( GameMode::FoulPush_,    RIGHT );
    M_playmode_map["foul_multiple_attack_l"] = std::make_pair( GameMode::FoulMultipleAttacker_, LEFT );
    M_playmode_map["foul_multiple_attack_r"] = std::make_pair( GameMode::FoulMultipleAttacker_, RIGHT );
    M_playmode_map["foul_ballout_l"]  = std::make_pair( GameMode::FoulBallOut_, LEFT );
    M_playmode_map["foul_ballout_r"]  = std::make_pair( GameMode::FoulBallOut_, RIGHT );
    M_playmode_map["back_pass_l"] = std::make_pair( GameMode::BackPass_,  LEFT );
    M_playmode_map["back_pass_r"] = std::make_pair( GameMode::BackPass_, RIGHT );
    M_playmode_map["free_kick_fault_l"] = std::make_pair( GameMode::FreeKickFault_, LEFT );
    M_playmode_map["free_kick_fault_r"] = std::make_pair( GameMode::FreeKickFault_, RIGHT );
    M_playmode_map["catch_fault_l"] = std::make_pair( GameMode::CatchFault_, LEFT );
    M_playmode_map["catch_fault_r"] = std::make_pair( GameMode::CatchFault_, RIGHT );
    M_playmode_map["indirect_free_kick_l"] = std::make_pair( GameMode::IndFreeKick_, LEFT );
    M_playmode_map["indirect_free_kick_r"] = std::make_pair( GameMode::IndFreeKick_, RIGHT );
    M_playmode_map["penalty_setup_l"] = std::make_pair( GameMode::PenaltySetup_, LEFT );
    M_playmode_map["penalty_setup_r"] = std::make_pair( GameMode::PenaltySetup_, RIGHT );
    M_playmode_map["penalty_ready_l"] = std::make_pair( GameMode::PenaltyReady_, LEFT );
    M_playmode_map["penalty_ready_r"] = std::make_pair( GameMode::PenaltyReady_, RIGHT );
    M_playmode_map["penalty_taken_l"] = std::make_pair( GameMode::PenaltyTaken_, LEFT );
    M_playmode_map["penalty_taken_r"] = std::make_pair( GameMode::PenaltyTaken_, RIGHT );
    M_playmode_map["penalty_miss_l"] = std::make_pair( GameMode::PenaltyMiss_, LEFT );
    M_playmode_map["penalty_miss_r"] = std::make_pair( GameMode::PenaltyMiss_, RIGHT );
    M_playmode_map["penalty_score_l"] = std::make_pair( GameMode::PenaltyScore_, LEFT );
    M_playmode_map["penalty_score_r"] = std::make_pair( GameMode::PenaltyScore_, RIGHT );

    //"goal_SIDE_SCORE"
    M_playmode_map["half_time"] = std::make_pair( GameMode::FirstHalfOver, NEUTRAL );
    M_playmode_map["time_extended"] = std::make_pair( GameMode::ExtendHalf, NEUTRAL );
    M_playmode_map["time_up_without_a_team"] = std::make_pair( GameMode::TimeOver, NEUTRAL );
    M_playmode_map["time_up"] = std::make_pair( GameMode::TimeOver, NEUTRAL );
    M_playmode_map["foul_l"] = std::make_pair( GameMode::FreeKick_, RIGHT );
    M_playmode_map["foul_r"] = std::make_pair( GameMode::FreeKick_, LEFT );
    M_playmode_map["goalie_catch_ball_l"] = std::make_pair( GameMode::GoalieCatch_, LEFT );
    M_playmode_map["goalie_catch_ball_r"] = std::make_pair( GameMode::GoalieCatch_, RIGHT );

    M_playmode_map["penalty_onfield_l"] = std::make_pair( GameMode::PenaltyOnfield_, LEFT );
    M_playmode_map["penalty_onfield_r"] = std::make_pair( GameMode::PenaltyOnfield_, RIGHT );
    M_playmode_map["penalty_foul_l"] = std::make_pair( GameMode::PenaltyFoul_, LEFT );
    M_playmode_map["penalty_foul_r"] = std::make_pair( GameMode::PenaltyFoul_, RIGHT );
    M_playmode_map["penalty_winner_l"] = std::make_pair( GameMode::TimeOver, NEUTRAL );//std::make_pair(PenaltyWinner_, LEFT);
    M_playmode_map["penalty_winner_r"] = std::make_pair( GameMode::TimeOver, NEUTRAL );//std::make_pair(PenaltyWinner_, RIGHT);
    M_playmode_map["penalty_draw"] = std::make_pair( GameMode::TimeOver, NEUTRAL );//std::make_pair(PenaltyDraw, NEUTRAL);
}

} // end of no name namespace

namespace rcsc {

/*-------------------------------------------------------------------*/
/*!

*/
GameMode::GameMode()
    : M_time( -1, 0 )
    , M_type( BeforeKickOff )
    , M_side( NEUTRAL )
    , M_score_left( 0 )
    , M_score_right( 0 )
{

}

/*-------------------------------------------------------------------*/
/*!

*/
bool
GameMode::update( const std::string & mode_str,
                  const GameTime & current )
{
    /*****
          (hear TIME referee PLAY_MODE)\n
    *****/

    // "offside_OURSIDE" playmode means (PM_Their_Offside_Kick)
    // "offside_OPPSIDE" playmode means (PM_My_Offside_Kick);

    Pair mode_pair = parse( mode_str );

    if ( mode_pair.first == MODE_MAX )
    {
        return false;
        //if ( current.cycle() == 0 ) mode_pair.first = BeforeKickOff;
        //else mode_pair.first = PlayOn;
        //mode_pair.second = NEUTRAL;
    }


    // when goalie catch the ball, playmode is changed twice at the same game cycle:
    //   PlayOn -> GoalieCatch_ -> FreeKick_
    // therefore, if old playmode is GoalieCatch_
    // we should not "immediately" change playmode to know what this is goalie kick phase.
    if ( M_type == GoalieCatch_ // last playmode is goalie_catch
         && mode_pair.first == FreeKick_ // new playmode is freekick
         && M_side == mode_pair.second // same side
         && M_time == current )   // and alse, same cycle
    {
        // do nothing
        // keep goalie catch mode
    }
    else // current playmode is NOT goalie catch
    {
        M_type = mode_pair.first;
        M_side = mode_pair.second;
    }

    M_time = current;

    return true;
}

/*-------------------------------------------------------------------*/
/*!

*/
GameMode::Pair
GameMode::parse( const std::string & mode_str )
{
    const PlayModeMap & pmap = MapHolder::instance().get();

    PlayModeMap::const_iterator it = pmap.find( mode_str );
    if ( it != pmap.end() )
    {
        return it->second;
    }

    if ( ! mode_str.compare( 0, 6, "goal_l") )
    {
        M_score_left = std::atoi( mode_str.substr( std::strlen( "goal_l_" ) ).c_str() );
        return std::make_pair( AfterGoal_, LEFT );
    }
    else if ( ! mode_str.compare( 0, 6, "goal_r" ) )
    {
        M_score_right = std::atoi( mode_str.substr( std::strlen( "goal_r_" ) ).c_str() );
        return std::make_pair( AfterGoal_, RIGHT );
    }

    //std::cerr << __FILE__ << ": " << __LINE__
    //          << " Received unsupported playmode : [" << mode_str << "]"
    //          << std::endl;

    return std::make_pair( MODE_MAX, NEUTRAL );
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
GameMode::isServerCycleStoppedMode() const
{
    switch ( type() ) {
    case BeforeKickOff:
    case AfterGoal_:
    case OffSide_:
    case FoulCharge_:
    case FoulPush_:
    case FreeKickFault_:
    case BackPass_:
    case CatchFault_:
        return true;
    default:
        return false;
    }
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
GameMode::isGameEndMode() const
{
    return ( type() == TimeOver );
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
GameMode::isPenaltyKickMode() const
{
    switch ( type() ) {
    case PenaltySetup_:
    case PenaltyReady_:
    case PenaltyTaken_:
    case PenaltyMiss_:
    case PenaltyScore_:
    case PenaltyOnfield_:
    case PenaltyFoul_:
        return true;
    default:
        return false;
    }

    return false;
}

/*-------------------------------------------------------------------*/
/*!

*/
bool
GameMode::isTeamsSetPlay( const SideID team_side ) const
{
    switch ( type() ) {
    case KickOff_:
    case KickIn_:
    case CornerKick_:
    case GoalKick_:
    case FreeKick_:
    case GoalieCatch_:
    case IndFreeKick_:
        if ( team_side == side() )
        {
            return true;
        }
        return false;
    case OffSide_:
    case FoulCharge_:
    case FoulPush_:
    case FreeKickFault_:
    case BackPass_:
    case CatchFault_:
        if ( team_side != side() )
        {
            return true;
        }
        return false;
    default:
        return false;
    }

    return false;
}

/*-------------------------------------------------------------------*/
/*!

*/
PlayMode
GameMode::getServerPlayMode() const
{
    switch ( type() ) {
    case BeforeKickOff:
        return PM_BeforeKickOff;
    case TimeOver:
        return PM_TimeOver;
    case PlayOn:
        return PM_PlayOn;
    case KickOff_:
        return ( side() == LEFT
                 ? PM_KickOff_Left
                 : PM_KickOff_Right );
    case KickIn_:
        return ( side() == LEFT
                 ? PM_KickIn_Left
                 : PM_KickIn_Right );
    case FreeKick_:
        return ( side() == LEFT
                 ? PM_FreeKick_Left
                 : PM_FreeKick_Right );
    case CornerKick_:
        return ( side() == LEFT
                 ? PM_CornerKick_Left
                 : PM_CornerKick_Right );
    case GoalKick_:
        return ( side() == LEFT
                 ? PM_GoalKick_Left
                 : PM_GoalKick_Right );
    case AfterGoal_:
        return ( side() == LEFT
                 ? PM_AfterGoal_Left
                 : PM_AfterGoal_Right );
        //Drop_Ball,   // Left | Right
    case OffSide_:
        return ( side() == LEFT
                 ? PM_OffSide_Left
                 : PM_OffSide_Right );
    case PenaltyKick_:
        return ( side() == LEFT
                 ? PM_PK_Left
                 : PM_PK_Right );
    case FirstHalfOver:
        return PM_FirstHalfOver;
    case Pause:
        return PM_Pause;
    case Human:
        return PM_Human;
    case FoulCharge_:
        return ( side() == LEFT
                 ? PM_Foul_Charge_Left
                 : PM_Foul_Charge_Right );
    case FoulPush_:
        return ( side() == LEFT
                 ? PM_Foul_Push_Left
                 : PM_Foul_Push_Right );
    case FoulMultipleAttacker_:
        return ( side() == LEFT
                 ? PM_Foul_MultipleAttacker_Left
                 : PM_Foul_MultipleAttacker_Right );
    case FoulBallOut_:
        return ( side() == LEFT
                 ? PM_Foul_BallOut_Left
                 : PM_Foul_BallOut_Right );
    case BackPass_:
        return ( side() == LEFT
                 ? PM_Back_Pass_Left
                 : PM_Back_Pass_Right );
    case FreeKickFault_:
        return ( side() == LEFT
                 ? PM_Free_Kick_Fault_Left
                 : PM_Free_Kick_Fault_Right );
    case CatchFault_:
        return ( side() == LEFT
                 ? PM_CatchFault_Left
                 : PM_CatchFault_Right );
    case IndFreeKick_:
        return ( side() == LEFT
                 ? PM_IndFreeKick_Left
                 : PM_IndFreeKick_Right );
    case PenaltySetup_:
        return ( side() == LEFT
                 ? PM_PenaltySetup_Left
                 : PM_PenaltySetup_Right );
    case PenaltyReady_:
        return ( side() == LEFT
                 ? PM_PenaltyReady_Left
                 : PM_PenaltyReady_Right );
    case PenaltyTaken_:
        return ( side() == LEFT
                 ? PM_PenaltyTaken_Left
                 : PM_PenaltyTaken_Right );
    case PenaltyMiss_:
        return ( side() == LEFT
                 ? PM_PenaltyMiss_Left
                 : PM_PenaltyMiss_Right );
    case PenaltyScore_:
        return ( side() == LEFT
                 ? PM_PenaltyScore_Left
                 : PM_PenaltyScore_Right );
    default:
        return PM_MAX;
    };
}

/*-------------------------------------------------------------------*/
/*!

*/
std::ostream &
GameMode::print( std::ostream & os ) const
{
    os << M_time;

    switch ( type() ) {
    case BeforeKickOff:
        os << " before_kick_off";
        break;
    case TimeOver:
        os << " game_over";
        break;
    case PlayOn:
        os << " play_on";
        break;
    case KickOff_:
        os << " kick_off";
        break;
    case KickIn_:
        os << " kick_in";
        break;
    case FreeKick_:
        os << " free_kick";
        break;
    case CornerKick_:
        os << " corner_kick";
        break;
    case GoalKick_:
        os << " goal_kick";
        break;
    case AfterGoal_:  // Left | Right
        os << "goal_?";
        break;
        //Drop_Ball,   // Left | Right
    case OffSide_:
        os << " offside";
        break;
        //PK_,         // Left | Right
    case FirstHalfOver:
        os << " half_time";
        break;
        //Pause,
        //Human,
    case FoulCharge_:
        os << " foul_charge";
        break;
    case FoulPush_:
        os << " foul_push";
        break;
        //Foul_MultipleAttacker_,
        //Foul_BallOut_,
    case BackPass_:
        os << " back_pass";
        break;
    case FreeKickFault_:
        os << " free_kick_fault";
        break;
    case CatchFault_:
        os << " catch_fault";
        break;
    case IndFreeKick_:
        os << " indirect_free_kick";
        break;
    case PenaltySetup_:
        os << " penalty_setup_";
        break;
    case PenaltyReady_:
        os << " penalty_ready";
        break;
    case PenaltyTaken_:
        os << "penalty_taken";
        break;
    case PenaltyMiss_:
        os << "penalty_miss";
        break;
    case PenaltyScore_:
        os << "penalty_score";
        break;
    case PenaltyOnfield_:
        os << "penalty_onfield_l";
        break;
    case PenaltyFoul_:
        os << "penalty_foul_l";
        break;
        //case PenaltyWinner_:
        //case PenaltyDraw:
    case GoalieCatch_:
        os << " goalie_catch";
        break;
    case ExtendHalf:
        os << " time_extend";
        break;
    default:
        os << " Unexpected playmode";
        break;
    }

    switch ( side() ) {
    case NEUTRAL:
        os << " Neutral";
        break;
    case LEFT:
        os << " Left";
        break;
    case RIGHT:
        os << " Right";
        break;
    default:
        os << " Unknown Side";
        break;
    }

    return os << std::endl;
}

}
