//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//
#import <UIKit/UIKit.h>

@interface OverviewCell : UITableViewCell{
    UILabel *titleL;
    UILabel *valueL;
    UILabel *informationL;
    UILabel *descriptionL;
}

-(instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier;
-(void)addComponents;
-(void)setValueLabelText:(NSString *)text;
-(void)setInformationLabelText:(NSString *)text;
-(void)setDescriptionLabelText:(NSString *)text;
-(void)setTitleText:(NSString *)text color:(UIColor *)color;

@end
