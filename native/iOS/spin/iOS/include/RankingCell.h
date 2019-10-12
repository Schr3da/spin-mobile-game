//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//
#import <UIKit/UIKit.h>

@interface RankingCell : UITableViewCell{
    UILabel *titleL;
    UILabel *positionL;
    UILabel *valueL;
}

-(instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier;
-(void)addComponents;
-(void)setPositionLabelText:(NSString *)text;
-(void)setValueLabelText:(NSString *)text;
-(void)setTitleText:(NSString *)text color:(UIColor *)color;

@end
